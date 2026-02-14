# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult
from collections import Counter


def search_and_rank_by_metadata_field(
    index_path: str,
    query: str,
    rank_by_field: str,
    top_k: int = 5
) -> List[SearchResult]:
    """Search in an index and rank results by a metadata field value.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        rank_by_field: Metadata field name to use for ranking (results with higher values ranked first)
        top_k: Number of results to return (default: 5)
        
    Returns:
        List of SearchResult objects, sorted by the specified metadata field value (descending), then by score
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)  # Get more results for ranking
    
    # Separate results by whether they have the ranking field
    with_field = []
    without_field = []
    
    for result in results:
        metadata = result.metadata or {}
        if rank_by_field in metadata:
            field_value = metadata[rank_by_field]
            # Only rank by numeric values
            if isinstance(field_value, (int, float)):
                with_field.append((field_value, result))
            else:
                without_field.append(result)
        else:
            without_field.append(result)
    
    # Sort by field value (descending), then by score
    with_field.sort(key=lambda x: (x[0], x[1].score), reverse=True)
    
    # Combine: results with field first (sorted), then results without field (by score)
    ranked_results = [result for _, result in with_field]
    ranked_results.extend(sorted(without_field, key=lambda x: x.score, reverse=True))
    
    return ranked_results[:top_k]
