import asyncio
import json
import os
import sys
from typing import List, Dict

from generation import generate_with_private_messages
import random
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor
from functools import partial
import time
import uuid
import re
import subprocess
import shutil
import threading
import queue
from tqdm import tqdm
import gc  # Add garbage collection

CONCURRENCY_LIMIT = 36

# Evaluation queue and control variables
evaluation_queue = queue.Queue()
evaluation_done = threading.Event()  # Used to notify evaluation thread to end
all_generation_done = threading.Event()  # Used to mark if all generation tasks are completed
build_lock = threading.Lock()  # Used to ensure only one build.sh is executing at a time

def sync_generate_with_messages(model_name, messages, prompt_id):
    """Synchronous version of generate_with_messages, for execution in thread pool"""
    # Since generate_with_messages is async but internally synchronous, we need to run in a new event loop
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    try:
        result = loop.run_until_complete(
            generate_with_private_messages(model_name, messages, prompt_id,
            # tags=["```cpp"]
            )
        )
        return result
    finally:
        loop.close()


async def generation(executor, model_name, query, semaphore):
    async with semaphore:
        loop = asyncio.get_event_loop()
        
        for attempt in range(1):
            # Execute synchronous API call in thread pool
            output = await loop.run_in_executor(
                executor,
                partial(
                    sync_generate_with_messages,
                    model_name=model_name,
                    prompt_id=str(uuid.uuid4()),
                    messages=[
                        {
                        "role": "system",
                        "content": "",
                        },
                        {
                            "role": "user",
                            "content": query["instruction"] 
                            # + query["ground truth context"]
                            #  + "<think>OK, I need to"
                        }
                    ]
                )
            )
            try:
                text_content = output['text'].strip()
                
                # Try multiple parsing methods
                result = None
                
                # Method 1: Find ```cpp...``` blocks, using non-greedy matching
                pattern = re.compile(r'```cpp\s*(.*?)\s*```', re.DOTALL)
                match = pattern.search(text_content)
                if match:
                    result = match.group(1).strip()
                
                if result is None:
                    pattern = re.compile(r'```c\+\+\s*(.*?)\s*```', re.DOTALL)
                    match = pattern.search(text_content)
                    if match:
                        result = match.group(1).strip()
                    else:
                        result = text_content.strip()
                
                if result is None:
                    result = text_content.strip()
                
            except Exception as e:
                pass
            
            if result is None:
                query["output"] = {
                    "messages": output['messages'],
                    "reasoning": output['reasoning'],
                    "text" : output['text'],
                    "result" : None
                }
            else:
                query["output"] = {
                    "messages": output['messages'],
                    "reasoning": output['reasoning'],
                    "text": output['text'],
                    "result": result
                }

            print("success")
            return query
        
        # query["output"] = None
        # return query


async def synthesize(queries: List[Dict], model_name, output_file: str):
    semaphore = asyncio.Semaphore(CONCURRENCY_LIMIT)
    
    
    with ThreadPoolExecutor(max_workers=CONCURRENCY_LIMIT) as executor:
        tasks = [
            asyncio.create_task(generation(executor, model_name, query, semaphore))
            for query in queries
        ]
        print(f"Starting concurrent execution of {len(tasks)} tasks...\n")
        results = await asyncio.gather(*tasks)
    
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(results, f, ensure_ascii=False, indent=4)

def get_test_case_content(original_test_case_content: str):
    original_test_case_content = original_test_case_content.split("\n")
    for i, line in enumerate(original_test_case_content):
        if line.strip().startswith("#include \"") and line.strip().endswith(".hpp\"") and "common/" not in line:
            original_test_case_content[i] = "#include \"implementation.hpp\""
            break
    return "\n".join(original_test_case_content)

def run_evaluation_for_single_file(input_json_file: str, output_json_dir: str, target_project_path: str):
    """
    Execute evaluation on a single generated result file (consistent with run_evaluation.py logic)
    """
    input_json_filename = os.path.basename(input_json_file)
    output_json = os.path.join(output_json_dir, input_json_filename)
    
    if os.path.exists(output_json):
        print(f"[Evaluation] Already exists {output_json}")
        return
    
    if not os.path.exists(output_json_dir):
        os.makedirs(output_json_dir)

    with open(input_json_file, 'r', encoding='utf-8') as f:
        results = json.load(f)
    
    print(f"[Evaluation] Starting evaluation: {input_json_file}")
    
    compile_success_cnt = 0
    test_success_cnt = 0
    null_cnt = 0
    
    for result in tqdm(results):
        target_function_path = os.path.join(target_project_path, "include", f"implementation.hpp")
        test_case_path = os.path.join(target_project_path, "tests", f"tests.cpp")
        # target_function_path = result["file path"]
        generate_result = result["output"]["result"]
        generate_result = re.findall(r'```python\s*(.*?)\s*```', generate_result, re.DOTALL)
        if generate_result:
            generate_result = generate_result[0]
        else:
            generate_result = result["output"]["result"]
        # generate_result = result["ground truth"]
        
        test_case_content = result["test cases"]
        # with open(result["test case path"], 'r', encoding='utf-8') as f:
        #     test_case_content = f.read()
        test_case_content = get_test_case_content(test_case_content)
        if not generate_result:
            null_cnt += 1
            continue
        
        # generate_result = generate_result.replace(
        #     "\ninline", 
        #     "\nusing namespace sqlgen;\nusing namespace sqlgen::literals;\ninline"
        # )
        
        result["evaluation_result"] = {}
        result["evaluation_message"] = {}
        
        # Backup
        shutil.copy(target_function_path, f"{target_function_path}.copy")
        
        try:
            # Write results
            with open(target_function_path, 'w', encoding='utf-8') as f:
                f.write(generate_result)
            
            with open(test_case_path, 'w', encoding='utf-8') as f:
                f.write(test_case_content)
            
            # Compile
            compile_proc = None
            max_compile_retries = 10  # Maximum retry count
            compile_retry_count = 0
            while compile_retry_count < max_compile_retries:
                try:
                    compile_proc = subprocess.run(
                        ["cmake", "--build", "build", "-j", "4"],
                        cwd=target_project_path,
                        capture_output=True,
                        timeout=300  # 5 minute timeout
                    )
                    compile_output = compile_proc.stdout.decode('utf-8', errors='replace')
                    compile_error = compile_proc.stderr.decode('utf-8', errors='replace')

                    if "Killed signal terminated program cc1plus" in compile_error:
                        compile_retry_count += 1
                        print(f"[Evaluation] Compilation killed, retry {compile_retry_count}/{max_compile_retries}")
                        continue
                    else:
                        break
                except subprocess.TimeoutExpired:
                    compile_retry_count += 1
                    print(f"[Evaluation] Compilation timeout, retry {compile_retry_count}/{max_compile_retries}")
                    compile_output = ""
                    compile_error = "Compilation timeout"
                    continue
            
            if compile_retry_count >= max_compile_retries:
                compile_output = ""
                compile_error = "Compilation retry limit exceeded"
            
            result["evaluation_message"]["compile_result"] = {
                "output": compile_output,
                "error": compile_error
            }
            
            if compile_error:
                result["evaluation_result"]["compile_result"] = False
                result["evaluation_result"]["test_result"] = False
                continue
            else:
                result["evaluation_result"]["compile_result"] = True
            
                        
            # Immediately release original output memory and process objects
            del compile_output, compile_error, compile_proc

            compile_success_cnt += 1
            
            # Test
            try:
                test_proc = subprocess.run(
                    ["ctest"],
                    cwd=os.path.join(target_project_path, "build"),
                    capture_output=True,
                    timeout=120  # 2 minute timeout
                )
                test_output = test_proc.stdout.decode('utf-8', errors='replace')
                test_error = test_proc.stderr.decode('utf-8', errors='replace')
            except subprocess.TimeoutExpired:
                test_output = ""
                test_error = "Test timeout"
            
            result["evaluation_message"]["test_result"] = {
                "output": test_output,
                "error": test_error
            }
            
            if test_error:
                result["evaluation_result"]["test_result"] = False
            else:
                result["evaluation_result"]["test_result"] = True
                test_success_cnt += 1
        
        finally:
            # Restore
            shutil.copy(f"{target_function_path}.copy", target_function_path)
            os.remove(f"{target_function_path}.copy")
    
    print(f"[Evaluation] {input_json_filename} - compile_success: {compile_success_cnt}, test_success: {test_success_cnt}, null: {null_cnt}, total: {len(results)}")
    print(f"[Evaluation] compile_rate: {compile_success_cnt/float(len(results)):.4f}, test_rate: {test_success_cnt/float(len(results)):.4f}")
    
    with open(output_json, 'w', encoding='utf-8') as f:
        json.dump(results, f, ensure_ascii=False, indent=4)
    
    print(f"[Evaluation] Output path: {output_json}")
    
    # Explicitly release memory
    del results
    gc.collect()

def create_project_copy(source_dir: str, copy_dir: str) -> str:
    """
    Create a working copy of the project
    
    Args:
        source_dir: Source project directory
        work_dir: Working directory (parent directory for copies)
        worker_id: Worker process ID
    
    Returns:
        Copy directory path
    """
    
    if os.path.exists(copy_dir):
        shutil.rmtree(copy_dir)
    
    # Copy project (excluding unnecessary large files)
    shutil.copytree(
        source_dir, 
        copy_dir,
        ignore=shutil.ignore_patterns(
            '*.o', '*.a', '.git', '__pycache__', 
            '*.pyc', 'CMakeFiles', 'Testing',
            "build"
        )
    )
    

    # Use lock to ensure only one build.sh is executing at a time, retry until successful
    with build_lock:
        start_time = time.time()
        max_build_retries = 10  # Maximum retry count
        build_retry_count = 0
        while build_retry_count < max_build_retries:
            try:
                compile_proc = subprocess.run(
                    ["./build.sh"],
                    cwd=copy_dir,
                    capture_output=True,
                    timeout=600  # 10 minute timeout
                )
                if compile_proc.returncode == 0:
                    print(f"[Build] {copy_dir} build successful, took {time.time() - start_time:.2f} seconds")
                    break
                else:
                    build_retry_count += 1
                    print(f"[Build] {copy_dir} build failed (return code: {compile_proc.returncode}), retry {build_retry_count}/{max_build_retries}...")
                    time.sleep(0.1)
            except subprocess.TimeoutExpired:
                build_retry_count += 1
                print(f"[Build] {copy_dir} build timeout, retry {build_retry_count}/{max_build_retries}...")
        
        if build_retry_count >= max_build_retries:
            raise RuntimeError(f"[Build] {copy_dir} build failed, maximum retry count {max_build_retries} reached")

    return copy_dir

def single_evaluation_task(task, output_json_dir: str, target_project_path: str):
    """
    Execute a single evaluation task
    
    Args:
        task: (model_name, input_json_file) tuple
        output_json_dir: Evaluation output directory
        target_project_path: Target project path
        task_id: Unique task ID for creating independent project copies
    """
    model_name, input_json_file = task
    
    input_json_filename = os.path.basename(input_json_file)
    output_json = os.path.join(output_json_dir, model_name, input_json_filename)
    if os.path.exists(output_json):
        print(f"[Evaluation] Already exists {output_json}")
        return

    copy_dir = None
    try:
        # Create unique project copy path for each parallel task
        copy_dir = create_project_copy(
            target_project_path, 
            target_project_path + "_" + input_json_file.replace(".json", "")
        )
        run_evaluation_for_single_file(input_json_file, os.path.join(output_json_dir, model_name), copy_dir)
        shutil.rmtree(copy_dir)
    except Exception as e:
        print(f"[Evaluation Thread] Evaluation failed: {input_json_file}, error: {e}")
    finally:
        # Ensure copy directory is cleaned up regardless of exceptions
        if copy_dir and os.path.exists(copy_dir):
            try:
                shutil.rmtree(copy_dir)
            except Exception as e:
                print(f"[Evaluation Thread] Failed to clean copy directory: {copy_dir}, error: {e}")


def evaluation_worker(output_json_dir: str, target_project_path: str, max_workers: int = 4):
    """
    Evaluation worker thread: Take tasks from queue and execute evaluations in parallel
    Multiple evaluation tasks can be executing at the same time
    
    Args:
        output_json_dir: Evaluation output directory
        target_project_path: Target project path
        max_workers: Maximum number of parallel evaluation tasks
    """
    from concurrent.futures import as_completed
    
    with ThreadPoolExecutor(max_workers=max_workers) as executor:
        pending_futures = {}  # Use dictionary to track ongoing tasks
        completed_count = 0
        
        while True:
            # Clean completed futures, release memory promptly
            done_keys = []
            for future_key, (future, task) in list(pending_futures.items()):
                if future.done():
                    try:
                        future.result()  # Get result (or exception)
                        completed_count += 1
                    except Exception as e:
                        print(f"[Evaluation Thread] Task execution exception: {task}, error: {e}")
                    done_keys.append(future_key)
            
            for key in done_keys:
                del pending_futures[key]
            
            try:
                # Try to get task from queue, timeout 1 second
                task = evaluation_queue.get(timeout=1)
                if task is None:  # Received end signal
                    break
                
                # Submit task to thread pool for parallel execution
                future = executor.submit(
                    single_evaluation_task, 
                    task, 
                    output_json_dir, 
                    target_project_path
                )
                pending_futures[id(future)] = (future, task)
                evaluation_queue.task_done()
                
            except queue.Empty:
                # Queue is empty, check if all generation tasks are completed
                if all_generation_done.is_set() and evaluation_queue.empty():
                    break
                continue
        
        # Wait for remaining tasks to complete
        print(f"[Evaluation Thread] Waiting for remaining {len(pending_futures)} parallel evaluation tasks to complete...")
        for future, task in pending_futures.values():
            try:
                future.result()
                completed_count += 1
            except Exception as e:
                print(f"[Evaluation Thread] Task execution exception: {task}, error: {e}")
        
        print(f"[Evaluation Thread] Completed {completed_count} evaluation tasks in total")
    
    print("[Evaluation Thread] Evaluation worker thread ended")


def run_model_generation(model_name: str, input_file: str, output_dir: str, enable_evaluation: bool):
    """
    Execute 10 serial generations for a single model
    Put evaluation task into queue after each generation is completed
    """
    print(f"[Model {model_name}] Starting generation tasks")
    
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for i in range(10):
        output_file = os.path.join(output_dir, f"{os.path.basename(input_file).split('.')[0]}_{model_name}_results_{i}.json")
        
        # Check if result file already exists, skip completed generations
        if os.path.exists(output_file):
            print(f"[Model {model_name}] Generation {i} already exists, skipping: {output_file}")
            if enable_evaluation:
                evaluation_queue.put((model_name, output_file))
                print(f"[Model {model_name}] Submitted evaluation task: {output_file}")
            continue
        
        with open(input_file, 'r', encoding='utf-8') as f:
            queries = json.load(f)
        # queries = queries[:1]
        
        print(f"[Model {model_name}] Starting generation {i}...")
        asyncio.run(synthesize(queries, model_name, output_file))
        print(f"[Model {model_name}] Generation {i} completed: {output_file}")
        
        # Explicitly release memory
        del queries
        gc.collect()
        
        # After generation is completed, put evaluation task into queue
        if enable_evaluation:
            evaluation_queue.put((model_name, output_file))
            print(f"[Model {model_name}] Submitted evaluation task: {output_file}")
    
    print(f"[Model {model_name}] All generation tasks completed")


if __name__ == "__main__":
    # print("wait")
    # time.sleep(60 * 5)
    
    # Argument 1: Model name(s) (multiple models separated by commas)
    model_names_str = sys.argv[1]
    model_names = [name.strip() for name in model_names_str.split(',')]
    
    input_file = sys.argv[2]
    output_dir = sys.argv[3]
    
    # New arguments: Evaluation output directory and target project path (optional)
    evaluation_output_dir = sys.argv[4] if len(sys.argv) > 4 else None
    target_project_path = sys.argv[5] if len(sys.argv) > 5 else None
    
    # Whether to enable evaluation
    enable_evaluation = evaluation_output_dir is not None and target_project_path is not None

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    if enable_evaluation and not os.path.exists(evaluation_output_dir):
        os.makedirs(evaluation_output_dir)
    
    print(f"=== Multi-Model Generation and Evaluation ===")
    print(f"Model list: {model_names}")
    print(f"Input file: {input_file}")
    print(f"Output directory: {output_dir}")
    print(f"Evaluation enabled: {enable_evaluation}")
    if enable_evaluation:
        print(f"Evaluation output directory: {evaluation_output_dir}")
        print(f"Target project path: {target_project_path}")
    print("=" * 40)
    
    # Start evaluation worker thread (execute evaluation tasks serially)
    evaluation_thread = None
    if enable_evaluation:
        evaluation_thread = threading.Thread(
            target=evaluation_worker,
            args=(evaluation_output_dir, target_project_path),
            daemon=True
        )
        evaluation_thread.start()
        print("[Main Process] Evaluation worker thread started")
    
    # Create a thread for each model, execute generation tasks in parallel
    model_threads = []
    for model_name in model_names:
        thread = threading.Thread(
            target=run_model_generation,
            args=(model_name, input_file, os.path.join(output_dir, model_name), enable_evaluation),
            name=f"Model-{model_name}"
        )
        model_threads.append(thread)
        thread.start()
        print(f"[Main Process] Generation thread for model {model_name} started")
    
    # Wait for all model generation threads to complete
    for thread in model_threads:
        thread.join()
    
    print("\n[Main Process] All model generation tasks completed")
    
    # Mark all generation tasks as completed
    all_generation_done.set()
    
    # Wait for evaluation queue to finish processing
    if enable_evaluation:
        print("[Main Process] Waiting for evaluation queue to finish processing...")
        evaluation_queue.join()  # Wait for all tasks in queue to complete
        
        # Send end signal to evaluation thread
        evaluation_queue.put(None)
        evaluation_thread.join()
        
        print("\n[Main Process] All evaluation tasks completed!")
    
    print("\n=== All tasks completed! ===")


# python3 run_test_private.py Qwen3-8B-api_oriented_rl_data_filtered-20251211-step65,Qwen3-8B-16GPU-2epochs-16k-highquality-filter-SFT-20251212,Qwen3-8B-32GPU-2epochs-8400iters-16k-highquality-20251210 test_case_en.json test_case_en_generate_result_20251214_without_reasoning_start_token test_case_en_evaluate_result_20251214_without_reasoning_start_token /data/workspace/Private-Model-Training/ConstructPrivateProject/search_library_usage/20251011121809/getml_sqlgen/sqlgen


# Qwen3-8B-32GPU-2epochs-4100iters-20251210,Qwen3-8B-32GPU-2epochs-4400iters-16k-highquality-20251209,Qwen3-8B-16GPU-2epochs-3100iters-4k-highquality-SFT-20251206,Qwen3-8B-16GPU-2epochs-4k-highquality-filter-SFT-200k-distill-random-20251208,Qwen3-8B-16GPU-2epochs-3100iters-20251208,Qwen3-8B-16GPU-2epochs-3100iters-16k-highquality-SFT-20251205,Qwen3-8B-16GPU-2epochs-4k-highquality-filter-SFT-200k-distill-20251207,Qwen3-8B-32GPU-2epochs-4k-highquality-filter-SFT-900k-distill-20251206,Qwen3-8B-16GPU-2epochs-4k-highquality-filter-SFT-200k-distill-20251206,Qwen3-8B-16GPU-2epochs-4k-highquality-filter-SFT-20251212,Qwen3-8B-16GPU-1epoch-4k-highquality-filter-SFT-20251212,Qwen3-8B-api_oriented_rl_data_filtered-20251212-step65,Qwen3-8B-api_oriented_rl_data_filtered-20251211-step65,Qwen3-8B-16GPU-2epochs-16k-highquality-filter-SFT-20251212,Qwen3-8B-32GPU-2epochs-8400iters-16k-highquality-20251210