# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult
from collections import Counter


def search_and_get_top_field_values(
    index_path: str,
    query: str,
    field_name: str,
    top_n: int = 5,
    search_top_k: int = 20
) -> List[tuple]:
    """Search in an index and return the top N most common field values in results.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        field_name: Metadata field name to analyze
        top_n: Number of top values to return (default: 5)
        search_top_k: Number of results to retrieve for analysis (default: 20)
        
    Returns:
        List of tuples (field_value, count) sorted by count (descending), limited to top_n
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If top_n <= 0
    """
    if top_n <= 0:
        raise ValueError("top_n must be greater than 0")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=search_top_k)
    
    # Count field values
    counter = Counter()
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(field_name)
        if field_value is not None:
            counter[field_value] += 1
    
    # Get top N
    top_values = counter.most_common(top_n)
    return top_values
