# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_complexity_adjustment(
    index_path: str,
    query: str,
    initial_complexity: int = 64,
    max_results: int = 10,
    min_score: float = 0.0
) -> List[SearchResult]:
    """Search in an index with adjustable complexity and score filtering.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        initial_complexity: Initial search complexity parameter (default: 64)
        max_results: Maximum number of results to return (default: 10)
        min_score: Minimum score threshold (default: 0.0)
        
    Returns:
        List of SearchResult objects with scores >= min_score, up to max_results
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If complexity is not in valid range [16, 128]
    """
    if initial_complexity < 16 or initial_complexity > 128:
        raise ValueError("complexity must be in range [16, 128]")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=max_results, complexity=initial_complexity)
    
    # Filter by minimum score
    filtered_results = [r for r in results if r.score >= min_score]
    
    return filtered_results
