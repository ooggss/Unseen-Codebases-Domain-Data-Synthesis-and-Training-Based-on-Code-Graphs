# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_field_weights(
    index_path: str,
    query: str,
    field_weights: Dict[str, float],
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and apply field-based score weighting.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        field_weights: Dictionary mapping metadata field names to weight multipliers
            Example: {"priority": 1.5, "rating": 1.2}
        top_k: Number of results to return (default: 10)
        
    Returns:
        List of SearchResult objects with adjusted scores based on field weights
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If any weight is negative
    """
    if any(weight < 0 for weight in field_weights.values()):
        raise ValueError("All field weights must be non-negative")
    
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)  # Get more results for weighting
    
    # Apply field weights to scores
    weighted_results = []
    for result in results:
        adjusted_score = result.score
        metadata = result.metadata or {}
        
        for field_name, weight in field_weights.items():
            if field_name in metadata:
                adjusted_score *= weight
        
        # Create new result with adjusted score
        weighted_result = SearchResult(
            id=result.id,
            score=adjusted_score,
            text=result.text,
            metadata=result.metadata
        )
        weighted_results.append(weighted_result)
    
    # Sort by adjusted score
    weighted_results.sort(key=lambda x: x.score, reverse=True)
    
    return weighted_results[:top_k]
