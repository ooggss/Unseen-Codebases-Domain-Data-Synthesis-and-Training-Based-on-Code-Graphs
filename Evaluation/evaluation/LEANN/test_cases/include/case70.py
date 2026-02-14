# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_field_priority(
    index_path: str,
    query: str,
    priority_field: str,
    priority_values: List[Any],
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and prioritize results based on field value order.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        priority_field: Metadata field name to use for prioritization
        priority_values: Ordered list of field values (earlier values have higher priority)
        top_k: Number of results to return (default: 10)
        
    Returns:
        List of SearchResult objects, sorted by priority (then by score)
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If priority_values is empty
    """
    if not priority_values:
        raise ValueError("priority_values cannot be empty")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)
    
    # Create priority map
    priority_map = {val: i for i, val in enumerate(priority_values)}
    
    # Separate results by priority
    prioritized_groups = {}
    unprioritized = []
    
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(priority_field)
        
        if field_value in priority_map:
            priority = priority_map[field_value]
            if priority not in prioritized_groups:
                prioritized_groups[priority] = []
            prioritized_groups[priority].append(result)
        else:
            unprioritized.append(result)
    
    # Sort each group by score, then combine by priority order
    sorted_results = []
    for priority in sorted(prioritized_groups.keys()):
        group = prioritized_groups[priority]
        group.sort(key=lambda x: x.score, reverse=True)
        sorted_results.extend(group)
    
    # Add unprioritized results at the end
    unprioritized.sort(key=lambda x: x.score, reverse=True)
    sorted_results.extend(unprioritized)
    
    return sorted_results[:top_k]
