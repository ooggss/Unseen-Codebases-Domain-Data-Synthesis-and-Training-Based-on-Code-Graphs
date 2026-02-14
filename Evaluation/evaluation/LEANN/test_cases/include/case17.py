
from typing import List, Dict, Any, Optional, Callable
from leann.api import SearchResult
from leann.metadata_filter import MetadataFilterEngine
from collections import defaultdict

def aggregate_search_results(
    search_results: List[SearchResult],
    group_by_field: str,
    aggregation_funcs: Optional[Dict[str, Callable]] = None
) -> Dict[str, Dict[str, Any]]:
    """Aggregate search results by a metadata field with optional statistics.
    
    Args:
        search_results: List of SearchResult objects to aggregate
        group_by_field: Metadata field name to group by
        aggregation_funcs: Optional dictionary mapping field_name to aggregation function.
            Example: {"score": max, "count": len}
            If None, defaults to count and average score per group
        
    Returns:
        Dictionary mapping group_value to aggregated statistics
        Example: {"tech": {"count": 5, "avg_score": 0.85, "max_score": 0.95}}
    """
    if not search_results:
        return {}
    
    # Group results by the specified field
    grouped = defaultdict(list)
    
    for result in search_results:
        group_value = result.metadata.get(group_by_field, "unknown")
        grouped[group_value].append(result)
    
    # Default aggregation functions
    if aggregation_funcs is None:
        aggregation_funcs = {
            "count": len,
            "avg_score": lambda results: sum(r.score for r in results) / len(results) if results else 0,
            "max_score": lambda results: max(r.score for r in results) if results else 0,
            "min_score": lambda results: min(r.score for r in results) if results else 0
        }
    
    # Aggregate statistics for each group
    aggregated = {}
    for group_value, results in grouped.items():
        group_stats = {}
        for stat_name, func in aggregation_funcs.items():
            try:
                group_stats[stat_name] = func(results)
            except Exception:
                # If aggregation fails, skip this statistic
                continue
        aggregated[group_value] = group_stats
    
    return aggregated