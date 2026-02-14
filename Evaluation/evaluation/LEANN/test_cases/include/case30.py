# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult
from collections import Counter


def search_and_count_by_field(
    index_path: str,
    query: str,
    count_by_field: str,
    top_k: int = 10
) -> Dict[str, int]:
    """Search in an index and count results by a metadata field value.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        count_by_field: Metadata field name to count by
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        Dictionary mapping field values to their counts in search results
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    # Count by field value
    counter = Counter()
    
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(count_by_field, "unknown")
        counter[field_value] += 1
    
    return dict(counter)
