# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_minimum_field_value(
    index_path: str,
    query: str,
    field_name: str,
    min_value: float,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and filter results by minimum numeric metadata field value.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        field_name: Metadata field name containing numeric values
        min_value: Minimum field value threshold
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        List of SearchResult objects with field values >= min_value
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)
    
    filtered_results = []
    
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(field_name)
        
        if field_value is not None:
            try:
                numeric_value = float(field_value)
                if numeric_value >= min_value:
                    filtered_results.append(result)
            except (ValueError, TypeError):
                # Skip non-numeric values
                continue
    
    return filtered_results
