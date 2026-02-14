# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_result_merging(
    index_path: str,
    queries: List[str],
    top_k_per_query: int = 3,
    global_top_k: int = 10
) -> List[SearchResult]:
    """Search an index with multiple queries and merge results.
    
    Args:
        index_path: Path to the LEANN index file
        queries: List of query strings to search with
        top_k_per_query: Number of results to retrieve per query (default: 3)
        global_top_k: Maximum number of results to return after merging (default: 10)
        
    Returns:
        List of SearchResult objects from all queries, deduplicated and sorted by score
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If queries list is empty
    """
    if not queries:
        raise ValueError("queries list cannot be empty")
    
    searcher = LeannSearcher(index_path=index_path)
    
    all_results = []
    seen_texts = set()
    
    for query in queries:
        results = searcher.search(query, top_k=top_k_per_query)
        
        for result in results:
            if result.text not in seen_texts:
                seen_texts.add(result.text)
                all_results.append(result)
    
    # Sort by score (descending)
    all_results.sort(key=lambda x: x.score, reverse=True)
    
    return all_results[:global_top_k]
