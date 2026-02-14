# function_implementation_file

from leann.api import LeannSearcher
from typing import List
from leann.api import SearchResult


def search_in_index(index_path: str, query: str, top_k: int = 5) -> List[SearchResult]:
    """Search for documents in a LEANN index.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        top_k: Number of top results to return (default: 5)
        
    Returns:
        List of SearchResult objects containing matching documents
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    return results

