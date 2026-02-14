# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_field_boost(
    index_path: str,
    query: str,
    boost_field: str,
    boost_value: Any,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and boost results that match a specific metadata field value.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        boost_field: Metadata field name to boost by
        boost_value: Field value to boost (results with this value will be ranked higher)
        top_k: Number of results to return (default: 10)
        
    Returns:
        List of SearchResult objects, with matching field values ranked first
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)  # Get more results for boosting
    
    # Separate results by whether they match the boost criteria
    boosted_results = []
    other_results = []
    
    for result in results:
        metadata = result.metadata or {}
        if metadata.get(boost_field) == boost_value:
            boosted_results.append(result)
        else:
            other_results.append(result)
    
    # Sort each group by score, then combine (boosted first)
    boosted_results.sort(key=lambda x: x.score, reverse=True)
    other_results.sort(key=lambda x: x.score, reverse=True)
    
    # Return boosted results first, then others
    return (boosted_results + other_results)[:top_k]
