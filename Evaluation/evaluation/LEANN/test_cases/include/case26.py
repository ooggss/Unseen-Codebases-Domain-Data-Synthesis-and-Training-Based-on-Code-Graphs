# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult
from collections import defaultdict


def search_and_group_by_metadata(
    index_path: str,
    query: str,
    group_by_field: str,
    top_k: int = 10
) -> Dict[str, List[SearchResult]]:
    """Search in an index and group results by a metadata field.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        group_by_field: Metadata field name to group results by
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        Dictionary mapping group values to lists of SearchResult objects in that group
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    # Group results by the specified field
    grouped = defaultdict(list)
    
    for result in results:
        metadata = result.metadata or {}
        group_value = metadata.get(group_by_field, "unknown")
        grouped[group_value].append(result)
    
    return dict(grouped)
