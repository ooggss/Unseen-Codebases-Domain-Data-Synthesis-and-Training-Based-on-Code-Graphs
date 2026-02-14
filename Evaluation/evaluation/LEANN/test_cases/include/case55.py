# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_custom_scoring(
    index_path: str,
    query: str,
    score_multiplier: float = 1.0,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and apply a custom score multiplier to all results.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        score_multiplier: Multiplier to apply to all scores (default: 1.0)
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        List of SearchResult objects with adjusted scores
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If score_multiplier < 0
    """
    if score_multiplier < 0:
        raise ValueError("score_multiplier must be non-negative")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    # Apply score multiplier
    adjusted_results = []
    for result in results:
        adjusted_score = result.score * score_multiplier
        adjusted_result = SearchResult(
            id=result.id,
            score=adjusted_score,
            text=result.text,
            metadata=result.metadata
        )
        adjusted_results.append(adjusted_result)
    
    return adjusted_results
