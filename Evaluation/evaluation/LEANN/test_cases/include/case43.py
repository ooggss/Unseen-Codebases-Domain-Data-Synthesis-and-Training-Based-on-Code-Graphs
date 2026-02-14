# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult
from collections import defaultdict


def search_multiple_indexes(
    index_paths: List[str],
    query: str,
    top_k_per_index: int = 3
) -> Dict[str, List[SearchResult]]:
    """Search across multiple indexes and return results grouped by index.
    
    Args:
        index_paths: List of paths to LEANN index files
        query: Search query string
        top_k_per_index: Number of results to retrieve from each index (default: 3)
        
    Returns:
        Dictionary mapping index_path to list of SearchResult objects from that index
        
    Raises:
        ValueError: If index_paths is empty
    """
    if not index_paths:
        raise ValueError("index_paths cannot be empty")
    
    results_by_index = {}
    
    for index_path in index_paths:
        try:
            searcher = LeannSearcher(index_path=index_path)
            results = searcher.search(query, top_k=top_k_per_index)
            results_by_index[index_path] = results
        except Exception:
            # If one index fails, continue with others
            results_by_index[index_path] = []
    
    return results_by_index


def merge_search_results(
    results_by_index: Dict[str, List[SearchResult]],
    global_top_k: int = 10,
    deduplicate: bool = True
) -> List[SearchResult]:
    """Merge search results from multiple indexes into a single ranked list.
    
    Args:
        results_by_index: Dictionary mapping index_path to list of SearchResult objects
        global_top_k: Maximum number of results to return after merging (default: 10)
        deduplicate: Whether to remove duplicate texts (default: True)
        
    Returns:
        List of SearchResult objects, sorted by score (descending), deduplicated if requested
    """
    all_results = []
    seen_texts = set()
    
    for index_path, results in results_by_index.items():
        for result in results:
            if deduplicate:
                if result.text not in seen_texts:
                    seen_texts.add(result.text)
                    # Add source index to metadata
                    if result.metadata is None:
                        result.metadata = {}
                    result.metadata['source_index'] = index_path
                    all_results.append(result)
            else:
                if result.metadata is None:
                    result.metadata = {}
                result.metadata['source_index'] = index_path
                all_results.append(result)
    
    # Sort by score (descending)
    all_results.sort(key=lambda x: x.score, reverse=True)
    
    return all_results[:global_top_k]
