# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_fuzzy_matching(
    index_path: str,
    query: str,
    top_k: int = 10,
    similarity_threshold: float = 0.5
) -> List[SearchResult]:
    """Search in an index and filter results by similarity threshold (fuzzy matching).
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        top_k: Maximum number of results to retrieve before filtering (default: 10)
        similarity_threshold: Minimum similarity score to include (default: 0.5)
        
    Returns:
        List of SearchResult objects with scores >= similarity_threshold
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If similarity_threshold is not in range [0, 1]
    """
    if similarity_threshold < 0 or similarity_threshold > 1:
        raise ValueError("similarity_threshold must be in range [0, 1]")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    # Filter by similarity threshold
    filtered_results = [r for r in results if r.score >= similarity_threshold]
    
    return filtered_results
