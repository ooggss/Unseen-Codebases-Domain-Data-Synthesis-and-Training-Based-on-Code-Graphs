# function_implementation_file

from typing import List, Optional, Dict, Any
from leann.api import SearchResult
from leann.metadata_filter import MetadataFilterEngine


def filter_search_results_by_metadata(
    search_results: List[SearchResult],
    metadata_filters: Optional[Dict[str, Dict[str, Any]]] = None
) -> List[SearchResult]:
    """Filter search results based on metadata criteria.
    
    Args:
        search_results: List of SearchResult objects to filter
        metadata_filters: Dictionary of filter specifications.
            Format: {"field_name": {"operator": value}}
            Example: {"topic": {"==": "programming"}, "category": {"in": ["AI", "ML"]}}
            
    Returns:
        Filtered list of SearchResult objects that match all criteria
    """
    if not metadata_filters:
        return search_results
    
    # Convert SearchResult objects to dictionaries
    result_dicts = []
    for result in search_results:
        result_dicts.append({
            "id": result.id,
            "score": result.score,
            "text": result.text,
            "metadata": result.metadata
        })
    
    # Apply filters using MetadataFilterEngine
    filter_engine = MetadataFilterEngine()
    filtered_dicts = filter_engine.apply_filters(result_dicts, metadata_filters)
    
    # Convert back to SearchResult objects
    filtered_results = []
    for result_dict in filtered_dicts:
        filtered_results.append(SearchResult(
            id=result_dict["id"],
            score=result_dict["score"],
            text=result_dict["text"],
            metadata=result_dict["metadata"]
        ))
    
    return filtered_results

