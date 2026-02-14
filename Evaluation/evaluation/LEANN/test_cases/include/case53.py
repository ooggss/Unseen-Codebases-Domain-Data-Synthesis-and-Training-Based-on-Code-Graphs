# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_result_limit_per_field(
    index_path: str,
    query: str,
    limit_field: str,
    max_per_value: int = 2,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and limit results per metadata field value.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        limit_field: Metadata field name to limit by
        max_per_value: Maximum number of results per field value (default: 2)
        top_k: Maximum number of results to retrieve before limiting (default: 10)
        
    Returns:
        List of SearchResult objects with at most max_per_value results per field value
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If max_per_value <= 0
    """
    if max_per_value <= 0:
        raise ValueError("max_per_value must be greater than 0")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    # Track counts per field value
    value_counts = {}
    limited_results = []
    
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(limit_field, "unknown")
        
        current_count = value_counts.get(field_value, 0)
        if current_count < max_per_value:
            limited_results.append(result)
            value_counts[field_value] = current_count + 1
    
    return limited_results
