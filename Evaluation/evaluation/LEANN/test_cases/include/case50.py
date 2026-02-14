# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult


def search_with_result_reranking(
    index_path: str,
    query: str,
    rerank_by_field: str,
    rerank_function: callable = None,
    top_k: int = 10
) -> List[SearchResult]:
    """Search in an index and rerank results based on a metadata field using a custom function.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        rerank_by_field: Metadata field name to use for reranking
        rerank_function: Optional function to compute rerank score from field value and original score.
            If None, uses field value directly (for numeric fields)
            Function signature: (field_value, original_score) -> rerank_score
        top_k: Number of results to return (default: 10)
        
    Returns:
        List of SearchResult objects, reranked by the specified field
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k * 2)
    
    # Rerank results
    reranked = []
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(rerank_by_field)
        
        if rerank_function:
            rerank_score = rerank_function(field_value, result.score)
        else:
            # Default: use field value if numeric, otherwise use original score
            if isinstance(field_value, (int, float)):
                rerank_score = float(field_value) * result.score
            else:
                rerank_score = result.score
        
        # Create new result with rerank score (store in metadata for tracking)
        reranked_result = SearchResult(
            id=result.id,
            score=rerank_score,
            text=result.text,
            metadata=result.metadata
        )
        reranked.append(reranked_result)
    
    # Sort by rerank score
    reranked.sort(key=lambda x: x.score, reverse=True)
    
    return reranked[:top_k]
