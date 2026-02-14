# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannSearcher, SearchResult
from collections import defaultdict


def search_and_aggregate_scores(
    index_path: str,
    query: str,
    aggregate_by_field: str,
    top_k: int = 10
) -> Dict[str, Dict[str, float]]:
    """Search in an index and aggregate scores by a metadata field.
    
    Args:
        index_path: Path to the LEANN index file
        query: Search query string
        aggregate_by_field: Metadata field name to aggregate by
        top_k: Number of results to retrieve (default: 10)
        
    Returns:
        Dictionary mapping field values to aggregated score statistics:
        {
            "field_value": {
                "count": number of results,
                "avg_score": average score,
                "max_score": maximum score,
                "min_score": minimum score
            }
        }
        
    Raises:
        FileNotFoundError: If index file is not found
    """
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    # Group results by field value
    grouped = defaultdict(list)
    
    for result in results:
        metadata = result.metadata or {}
        field_value = metadata.get(aggregate_by_field, "unknown")
        grouped[field_value].append(result.score)
    
    # Aggregate statistics
    aggregated = {}
    for field_value, scores in grouped.items():
        if scores:
            aggregated[field_value] = {
                "count": len(scores),
                "avg_score": sum(scores) / len(scores),
                "max_score": max(scores),
                "min_score": min(scores)
            }
    
    return aggregated
