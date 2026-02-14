# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_result_expansion(
    index_path: str,
    query: str,
    expand_by_field: str,
    expansion_count: int = 1,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and expand results by including additional results with matching field values.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        expand_by_field: Metadata field name to use for expansion
        expansion_count: Number of additional results to include per unique field value (default: 1)
        top_k: Number of initial results to retrieve (default: 10)
        
    Returns:
        List of SearchResult objects including expanded results
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If expansion_count < 0
    """
    if expansion_count < 0:
        raise ValueError("expansion_count must be non-negative")
    
    searcher = LeannSearcher(index_path=index_path)
    initial_results = searcher.search(query, top_k=top_k)
    
    # Collect field values from initial results
    field_values = set()
    for result in initial_results:
        metadata = result.metadata or {}
        field_value = metadata.get(expand_by_field)
        if field_value is not None:
            field_values.add(field_value)
    
    # Get more results for expansion
    expanded_results = list(initial_results)
    all_results = searcher.search(query, top_k=top_k * 2)
    
    # Add expansion results
    value_counts = {}
    for result in all_results:
        if result in initial_results:
            continue
        
        metadata = result.metadata or {}
        field_value = metadata.get(expand_by_field)
        
        if field_value in field_values:
            current_count = value_counts.get(field_value, 0)
            if current_count < expansion_count:
                expanded_results.append(result)
                value_counts[field_value] = current_count + 1
    
    return expanded_results
