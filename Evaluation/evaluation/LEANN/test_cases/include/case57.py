# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_and_extract_field_values(
    index_path: str,
    query: str,
    extract_field: str,
    top_k: int = 10
) -> List[Any]:
    """Search in an index and extract unique values of a metadata field from results.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        extract_field: Metadata field name to extract values from
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        List of unique field values found in search results (order preserved by first occurrence)
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    seen_values = set()
    unique_values = []
    
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(extract_field)
        
        if field_value is not None and field_value not in seen_values:
            seen_values.add(field_value)
            unique_values.append(field_value)
    
    return unique_values
