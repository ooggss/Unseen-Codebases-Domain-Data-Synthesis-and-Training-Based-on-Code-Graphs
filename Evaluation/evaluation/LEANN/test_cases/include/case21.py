# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult
from pathlib import Path


def search_with_metadata_filtering(
    index_path: str,
    query: str,
    metadata_filters: Dict[str, Dict[str, Any]],
    top_k: int = 5
) -> List[SearchResult]:
    """Search in an index and apply metadata filters to results.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        metadata_filters: Dictionary of filter specifications.
            Format: {"field_name": {"operator": value}}
            Example: {"category": {"==": "tech"}, "rating": {">=": 4.0}}
        top_k: Number of results to retrieve (default: 5)
        
    Returns:
        List of SearchResult objects that match both the query and metadata filters
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)  # Get more results for filtering
    
    # Apply metadata filters
    filtered_results = []
    for result in results:
        matches = True
        result_metadata = result.metadata or {}
        
        for field_name, filter_condition in metadata_filters.items():
            field_value = result_metadata.get(field_name)
            
            for operator, expected_value in filter_condition.items():
                if operator == "==":
                    if field_value != expected_value:
                        matches = False
                        break
                elif operator == "!=":
                    if field_value == expected_value:
                        matches = False
                        break
                elif operator == ">=":
                    if not (isinstance(field_value, (int, float)) and field_value >= expected_value):
                        matches = False
                        break
                elif operator == "<=":
                    if not (isinstance(field_value, (int, float)) and field_value <= expected_value):
                        matches = False
                        break
                elif operator == "in":
                    if field_value not in expected_value:
                        matches = False
                        break
                elif operator == "contains":
                    if expected_value not in str(field_value):
                        matches = False
                        break
            
            if not matches:
                break
        
        if matches:
            filtered_results.append(result)
            if len(filtered_results) >= top_k:
                break
    
    return filtered_results
