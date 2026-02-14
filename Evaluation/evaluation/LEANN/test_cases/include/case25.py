# function_implementation_file

from typing import List, Dict, Any, Optional
from leann.api import compute_embeddings
import numpy as np


def compute_similarity_between_texts(
    text1: str,
    text2: str,
    model_name: str = "facebook/contriever",
    mode: str = "sentence-transformers"
) -> float:
    """Compute cosine similarity between two text strings using embeddings.
    
    Args:
        text1: First text string
        text2: Second text string
        model_name: Name of the embedding model to use (default: "facebook/contriever")
        mode: Embedding backend mode (default: "sentence-transformers")
        
    Returns:
        Cosine similarity score between the two texts (range: -1 to 1, typically 0 to 1)
        
    Raises:
        ValueError: If either text is empty
    """
    if not text1 or not text2:
        raise ValueError("Both texts must be non-empty")
    
    # Compute embeddings for both texts
    embeddings = compute_embeddings(
        chunks=[text1, text2],
        model_name=model_name,
        mode=mode,
        use_server=False,
        is_build=False
    )
    
    emb1 = np.array(embeddings[0])
    emb2 = np.array(embeddings[1])
    
    # Compute cosine similarity
    dot_product = np.dot(emb1, emb2)
    norm1 = np.linalg.norm(emb1)
    norm2 = np.linalg.norm(emb2)
    
    if norm1 == 0 or norm2 == 0:
        return 0.0
    
    similarity = dot_product / (norm1 * norm2)
    return float(similarity)
