# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_timeout(
    index_path: str,
    query: str,
    top_k: int = 10,
    timeout_seconds: float = 5.0
) -> List[SearchResult]:
    """Search in an index with a timeout constraint.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        top_k: Number of results to retrieve (default: 10)
        timeout_seconds: Maximum time allowed for search in seconds (default: 5.0)
        
    Returns:
        List of SearchResult objects (may be empty if timeout occurs)
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If timeout_seconds <= 0
    """
    if timeout_seconds <= 0:
        raise ValueError("timeout_seconds must be greater than 0")
    
    import signal
    
    class TimeoutError(Exception):
        pass
    
    def timeout_handler(signum, frame):
        raise TimeoutError("Search operation timed out")
    
    # Set up timeout (Unix only)
    try:
        signal.signal(signal.SIGALRM, timeout_handler)
        signal.alarm(int(timeout_seconds))
    except (AttributeError, OSError):
        # Windows doesn't support SIGALRM, skip timeout
        pass
    
    try:
        searcher = LeannSearcher(index_path=index_path)
        results = searcher.search(query, top_k=top_k)
        return results
    except TimeoutError:
        return []
    finally:
        try:
            signal.alarm(0)  # Cancel alarm
        except (AttributeError, OSError):
            pass
