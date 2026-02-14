# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_field_aggregation(
    index_path: str,
    query: str,
    aggregate_field: str,
    top_k: int = 10
) -> Dict[str, List[SearchResult]]:
    """Search in an index and group results by a metadata field.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        aggregate_field: Metadata field name to group results by
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        Dictionary mapping field values to lists of SearchResult objects
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    grouped = {}
    
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(aggregate_field, "unknown")
        
        if field_value not in grouped:
            grouped[field_value] = []
        grouped[field_value].append(result)
    
    return grouped
