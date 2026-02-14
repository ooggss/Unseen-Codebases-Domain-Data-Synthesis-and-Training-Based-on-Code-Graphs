# function_implementation_file

from typing import List, Dict, Any, Optional
from leann.api import LeannSearcher, SearchResult


def search_with_score_threshold(
    index_path: str,
    query: str,
    min_score: float,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and filter results by minimum score threshold.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        min_score: Minimum similarity score threshold (results below this will be filtered out)
        top_k: Maximum number of results to retrieve before filtering (default: 10)
        
    Returns:
        List of SearchResult objects with scores >= min_score, sorted by score (descending)
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If min_score is not in valid range [0, 1] for cosine similarity
    """
    if min_score < 0 or min_score > 1:
        raise ValueError("min_score must be in range [0, 1]")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    # Filter by score threshold
    filtered_results = [r for r in results if r.score >= min_score]
    
    # Results are already sorted by score (descending) from searcher
    return filtered_results
