# function_implementation_file

from typing import List, Dict, Any, Optional
from leann.api import compute_embeddings
import numpy as np


def find_most_similar_text(
    query_text: str,
    candidate_texts: List[str],
    model_name: str = "facebook/contriever",
    mode: str = "sentence-transformers"
) -> Dict[str, Any]:
    """Find the most similar text from a list of candidates using embedding similarity.
    
    Args:
        query_text: Query text to find similarity for
        candidate_texts: List of candidate text strings to compare against
        model_name: Name of the embedding model to use (default: "facebook/contriever")
        mode: Embedding backend mode (default: "sentence-transformers")
        
    Returns:
        Dictionary containing:
        {
            "most_similar_text": the text with highest similarity,
            "similarity_score": the similarity score,
            "index": the index of the most similar text in candidate_texts
        }
        
    Raises:
        ValueError: If query_text is empty or candidate_texts is empty
    """
    if not query_text:
        raise ValueError("query_text cannot be empty")
    
    if not candidate_texts:
        raise ValueError("candidate_texts cannot be empty")
    
    # Compute embeddings for query and all candidates
    all_texts = [query_text] + candidate_texts
    embeddings = compute_embeddings(
        chunks=all_texts,
        model_name=model_name,
        mode=mode,
        use_server=False,
        is_build=False
    )
    
    query_emb = np.array(embeddings[0])
    candidate_embs = [np.array(emb) for emb in embeddings[1:]]
    
    # Compute cosine similarities
    best_index = 0
    best_score = -1.0
    
    for i, cand_emb in enumerate(candidate_embs):
        dot_product = np.dot(query_emb, cand_emb)
        norm_query = np.linalg.norm(query_emb)
        norm_cand = np.linalg.norm(cand_emb)
        
        if norm_query > 0 and norm_cand > 0:
            similarity = dot_product / (norm_query * norm_cand)
            if similarity > best_score:
                best_score = similarity
                best_index = i
    
    return {
        "most_similar_text": candidate_texts[best_index],
        "similarity_score": float(best_score),
        "index": best_index
    }
