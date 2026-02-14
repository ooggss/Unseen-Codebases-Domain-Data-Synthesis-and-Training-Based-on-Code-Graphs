# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_field_requirement(
    index_path: str,
    query: str,
    required_field: str,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and only return results that have a specific metadata field.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        required_field: Metadata field name that must be present in results
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        List of SearchResult objects that have the required field
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)
    
    filtered_results = []
    for result in results:
        metadata = result.metadata or {}
        if required_field in metadata:
            filtered_results.append(result)
            if len(filtered_results) >= top_k:
                break
    
    return filtered_results
