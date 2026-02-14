# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult
from datetime import datetime


def search_with_recency_boost(
    index_path: str,
    query: str,
    date_field: str,
    recency_days: int = 30,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and boost results based on recency of a date field.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        date_field: Metadata field name containing a date (ISO format string or timestamp)
        recency_days: Number of days to consider as "recent" (default: 30)
        top_k: Number of results to return (default: 10)
        
    Returns:
        List of SearchResult objects with recent results ranked higher
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If recency_days <= 0
    """
    if recency_days <= 0:
        raise ValueError("recency_days must be greater than 0")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)
    
    now = datetime.now()
    recent_results = []
    old_results = []
    
    for result in results:
        metadata = result.metadata or {}
        date_value = metadata.get(date_field)
        
        is_recent = False
        if date_value:
            try:
                # Try to parse as ISO format string
                if isinstance(date_value, str):
                    date_obj = datetime.fromisoformat(date_value.replace('Z', '+00:00'))
                elif isinstance(date_value, (int, float)):
                    # Assume timestamp
                    date_obj = datetime.fromtimestamp(date_value)
                else:
                    date_obj = None
                
                if date_obj:
                    days_ago = (now - date_obj.replace(tzinfo=None)).days
                    is_recent = days_ago <= recency_days
            except (ValueError, TypeError):
                pass
        
        if is_recent:
            recent_results.append(result)
        else:
            old_results.append(result)
    
    # Sort each group by score, then combine (recent first)
    recent_results.sort(key=lambda x: x.score, reverse=True)
    old_results.sort(key=lambda x: x.score, reverse=True)
    
    return (recent_results + old_results)[:top_k]
