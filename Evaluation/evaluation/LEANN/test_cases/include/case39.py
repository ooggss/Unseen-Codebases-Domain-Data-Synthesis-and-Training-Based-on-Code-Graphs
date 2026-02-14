# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_diversity_filtering(
    index_path: str,
    query: str,
    diversity_field: str,
    max_per_group: int = 2,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and ensure diversity by limiting results per metadata field value.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        diversity_field: Metadata field name to ensure diversity by
        max_per_group: Maximum number of results per field value (default: 2)
        top_k: Maximum number of results to retrieve before filtering (default: 10)
        
    Returns:
        List of SearchResult objects with diversity ensured (max max_per_group per field value)
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If max_per_group <= 0
    """
    if max_per_group <= 0:
        raise ValueError("max_per_group must be greater than 0")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    # Group by field value and limit per group
    grouped = {}
    diverse_results = []
    
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(diversity_field, "unknown")
        
        if field_value not in grouped:
            grouped[field_value] = 0
        
        if grouped[field_value] < max_per_group:
            diverse_results.append(result)
            grouped[field_value] += 1
    
    return diverse_results
