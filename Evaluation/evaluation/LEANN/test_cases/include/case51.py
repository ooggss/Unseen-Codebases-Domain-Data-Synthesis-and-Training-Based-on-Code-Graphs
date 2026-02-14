# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_field_exclusion(
    index_path: str,
    query: str,
    exclude_field: str,
    exclude_values: List[Any],
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and exclude results based on metadata field values.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        exclude_field: Metadata field name to filter by exclusion
        exclude_values: List of field values to exclude from results
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        List of SearchResult objects that do not have the excluded field values
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If exclude_values is empty
    """
    if not exclude_values:
        raise ValueError("exclude_values cannot be empty")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)
    
    exclude_set = set(exclude_values)
    filtered_results = []
    
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(exclude_field)
        
        if field_value not in exclude_set:
            filtered_results.append(result)
            if len(filtered_results) >= top_k:
                break
    
    return filtered_results
