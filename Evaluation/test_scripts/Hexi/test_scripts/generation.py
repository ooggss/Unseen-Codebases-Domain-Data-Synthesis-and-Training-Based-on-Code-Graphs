import os
import openai
import logging
import time
import requests
import json


def is_valid_with_tags(text, tags):
    """
    Validate whether the generated text contains required XML tags
    
    Check if the generated content includes complete question, answer, analysis tags,
    and each tag appears at least once to ensure correct format.
    
    Args:
        text (str): The text content to validate
        
    Returns:
        bool: True if text format is valid, False otherwise
    """
    for tag in tags:
        if text.count(tag) < 1:
            return False
    return True

async def generate_with_private_messages(model_name, messages, prompt_id, tags=[]):
    """
    Generate content using private API service
    
    Call internal streaming server API to generate content, providing an alternative to OpenAI API.
    Also includes retry mechanism and content validation.
    
    Args:
        model_name (str): Name of the model to use
        messages (list): List of messages
        prompt_id (str): Prompt ID for logging purposes
        
    Returns:
        dict: Dictionary containing prompt, reasoning process and generated text
    """
    # Private API service configuration

    # Maximum 100 retries
    for retry_times in range(50):
        
        enable_stream = False


        try:
            # Construct request data
            json_data = {
                "model": model_name,
                "query_id": prompt_id,
                "messages": messages,
                "temperature": 0,
                "output_seq_len": 20480,
                "max_input_seq_len": 10240,
                "stream": enable_stream,
                "top_k": 10,
                "top_p": 0.7,
                "repetition_penalty": 1.03,
                "compatible_with_openai": True
            }
            resp = requests.post(ss_url, headers=headers, json=json_data, stream=False, timeout=300000)
            reasoning_content = resp.json()['choices'][0]['message']['reasoning_content']
            text = resp.json()['choices'][0]['message']['content']
            usage_info = resp.json()['usage']

            if is_valid_with_tags(text, tags):
                logging.info(f"{model_name}: Prompt {prompt_id} completed")
                break
            else:
                logging.error(f"{model_name}: Invalid response, retrying...")
                time.sleep(0.1)
        except Exception as e:
            logging.error(f"{model_name}: Connection error, retrying...")
            time.sleep(0.1)
            
    if retry_times >= 99:
        logging.error(f"{model_name}: Prompt {prompt_id} failed after 100 retries")
    result = {
        "messages": messages,
        "reasoning": reasoning_content,
        "text": text,
        "usage_info": usage_info,
        "model_name": model_name
    }    
    return result
