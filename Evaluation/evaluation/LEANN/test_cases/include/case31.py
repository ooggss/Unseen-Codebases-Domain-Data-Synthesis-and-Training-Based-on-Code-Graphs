# function_implementation_file

from typing import List, Dict, Any, Optional
from leann.api import LeannChat
from pathlib import Path

@@ -19,9 +19,7 @@ def ask_question_with_context(
        question: Question to ask
        top_k: Number of context passages to retrieve (default: 20)
        llm: LLM provider to use (default: "ollama")
            Options: "ollama", "simulated", "hf", "openai", "anthropic", "gemini"
        model: Model name to use (default: "qwen3:8b")
            For "simulated" mode, this parameter is ignored
        
    Returns:
        Answer string from the LLM
@@ -33,16 +31,6 @@ def ask_question_with_context(
    if not question or not question.strip():
        raise ValueError("question cannot be empty")

    # Convert llm string to llm_config dictionary format expected by LeannChat
    llm_config = {
        "type": llm,
        "model": model
    }
    
    # For simulated mode, model is not needed
    if llm == "simulated":
        llm_config = {"type": "simulated"}
    
    chat = LeannChat(index_path=index_path, llm_config=llm_config)
    answer = chat.ask(question, top_k=top_k)
    return answer
