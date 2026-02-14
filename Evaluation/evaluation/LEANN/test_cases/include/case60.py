# function_implementation_file

from typing import List, Dict, Any
from leann.api import compute_embeddings
import numpy as np


def compute_text_similarity_matrix(
    texts: List[str],
    model_name: str = "facebook/contriever",
    mode: str = "sentence-transformers"
) -> np.ndarray:
    """Compute pairwise similarity matrix for a list of texts using embeddings.
    
    Args:
        texts: List of text strings to compute similarities for
        model_name: Name of the embedding model to use (default: "facebook/contriever")
        mode: Embedding backend mode (default: "sentence-transformers")
        
    Returns:
        NumPy array of shape (len(texts), len(texts)) containing pairwise cosine similarities
        
    Raises:
        ValueError: If texts list is empty
    """
    if not texts:
        raise ValueError("texts list cannot be empty")
    
    # Compute embeddings for all texts
    embeddings = compute_embeddings(
        chunks=texts,
        model_name=model_name,
        mode=mode,
        use_server=False,
        is_build=False
    )
    
    embeddings_array = np.array(embeddings)
    n = len(texts)
    similarity_matrix = np.zeros((n, n))
    
    # Compute pairwise cosine similarities
    for i in range(n):
        for j in range(n):
            emb_i = embeddings_array[i]
            emb_j = embeddings_array[j]
            
            dot_product = np.dot(emb_i, emb_j)
            norm_i = np.linalg.norm(emb_i)
            norm_j = np.linalg.norm(emb_j)
            
            if norm_i > 0 and norm_j > 0:
                similarity = dot_product / (norm_i * norm_j)
                # Clip to valid range [-1, 1] to handle floating point precision issues
                similarity = np.clip(similarity, -1.0, 1.0)
            else:
                similarity = 0.0
            
            similarity_matrix[i, j] = similarity
    
    return similarity_matrix
