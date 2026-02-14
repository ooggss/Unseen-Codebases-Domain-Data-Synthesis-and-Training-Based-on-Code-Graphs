# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_score_normalization(
    index_path: str,
    query: str,
    normalize_to_range: tuple = (0.0, 1.0),
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and normalize result scores to a specified range.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        normalize_to_range: Target range (min, max) for normalized scores (default: (0.0, 1.0))
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        List of SearchResult objects with normalized scores
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If normalize_to_range is invalid
    """
    if len(normalize_to_range) != 2:
        raise ValueError("normalize_to_range must be a tuple of (min, max)")
    
    min_val, max_val = normalize_to_range
    if min_val >= max_val:
        raise ValueError("normalize_to_range min must be less than max")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    if not results:
        return results
    
    # Find min and max scores
    scores = [r.score for r in results]
    score_min = min(scores)
    score_max = max(scores)
    
    # Normalize scores
    normalized_results = []
    score_range = score_max - score_min
    
    for result in results:
        if score_range > 0:
            normalized_score = min_val + (result.score - score_min) / score_range * (max_val - min_val)
        else:
            normalized_score = (min_val + max_val) / 2.0
        
        normalized_result = SearchResult(
            id=result.id,
            score=normalized_score,
            text=result.text,
            metadata=result.metadata
        )
        normalized_results.append(normalized_result)
    
    return normalized_results
