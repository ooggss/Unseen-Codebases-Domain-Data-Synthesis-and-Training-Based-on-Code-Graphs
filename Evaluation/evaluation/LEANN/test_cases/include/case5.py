# function_implementation_file

from typing import List
import numpy as np
from leann.api import compute_embeddings


def compute_text_embeddings(texts: List[str], model_name: str = "facebook/contriever", mode: str = "sentence-transformers") -> np.ndarray:
    """Compute embeddings for a list of text strings.
    
    Args:
        texts: List of text strings to embed
        model_name: Name of the embedding model to use (default: "facebook/contriever")
        mode: Embedding backend mode (default: "sentence-transformers")
            Options: "sentence-transformers", "mlx", "openai", "ollama"
        
    Returns:
        NumPy array of embeddings with shape (num_texts, embedding_dimension) and dtype float32
    """
    embeddings = compute_embeddings(
        chunks=texts,
        model_name=model_name,
        mode=mode,
        use_server=False,  # Direct computation (not via server)
        is_build=False
    )
    
    # Ensure the output is float32 or float64 (convert from float16 if needed)
    if embeddings.dtype == np.float16:
        embeddings = embeddings.astype(np.float32)
    elif embeddings.dtype not in (np.float32, np.float64):
        embeddings = embeddings.astype(np.float32)
    
    return embeddings

