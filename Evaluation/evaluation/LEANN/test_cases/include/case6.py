# function_implementation_file

from typing import Optional, Dict, Any
from leann.api import LeannChat


def ask_question(index_path: str, question: str, top_k: int = 5, model: str = "qwen3:8b", llm: str = "ollama") -> str:
    """Ask a question to a LEANN index using LLM.
    
    Args:
        index_path: Path to the LEANN index file
        question: Question to ask
        top_k: Number of top documents to retrieve for context (default: 5)
        model: LLM model name (default: "qwen3:8b")
        llm: LLM provider type (default: "ollama")
            Options: "ollama", "simulated", "hf", "openai", "anthropic"
            
    Returns:
        Answer string from the LLM
    """
    # Configure LLM
    llm_config = {
        "type": llm,
        "model": model
    }
    
    # Create chat instance
    chat = LeannChat(index_path=index_path, llm_config=llm_config)
    
    # Ask question and get response
    response = chat.ask(
        question=question,
        top_k=top_k
    )
    
    return response

