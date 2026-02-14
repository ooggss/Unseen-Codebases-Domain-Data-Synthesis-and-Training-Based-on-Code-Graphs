# function_implementation_file

from typing import List, Dict, Any, Optional, Callable
from leann.api import SearchResult
from leann.metadata_filter import MetadataFilterEngine
from collections import defaultdict


def apply_dynamic_filters(
    search_results: List[SearchResult],
    filter_specs: Dict[str, Dict[str, Any]],
    filter_logic: str = "AND"
) -> List[SearchResult]:
    """Apply dynamic metadata filters to search results with configurable logic.
    
    Args:
        search_results: List of SearchResult objects to filter
        filter_specs: Dictionary of filter specifications.
            Format: {"field_name": {"operator": value}}
            Example: {"category": {"==": "tech"}, "rating": {">=": 4.0}}
        filter_logic: "AND" (all filters must match) or "OR" (any filter matches)
        
    Returns:
        Filtered list of SearchResult objects
    """
    if not filter_specs:
        return search_results
    
    if filter_logic not in ["AND", "OR"]:
        raise ValueError("filter_logic must be 'AND' or 'OR'")
    
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
    
    if filter_logic == "AND":
        # Apply all filters - results must match all criteria
        filtered_dicts = filter_engine.apply_filters(result_dicts, filter_specs)
    else:
        # OR logic - results must match at least one filter
        # Apply each filter separately and combine results
        all_matching_ids = set()
        for field_name, filter_condition in filter_specs.items():
            single_filter = {field_name: filter_condition}
            filtered = filter_engine.apply_filters(result_dicts, single_filter)
            all_matching_ids.update(dict_item["id"] for dict_item in filtered)
        
        # Return results that match any filter
        filtered_dicts = [d for d in result_dicts if d["id"] in all_matching_ids]
    
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