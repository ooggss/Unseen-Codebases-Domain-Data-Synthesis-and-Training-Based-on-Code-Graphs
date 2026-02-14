# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannBuilder, LeannSearcher
from pathlib import Path


def build_and_verify_searchable(
    documents: List[Dict[str, Any]],
    index_path: str,
    test_query: str = "test",
    backend_name: str = "hnsw"
) -> Dict[str, Any]:
    """Build an index and verify it is searchable.
    
    Args:
        documents: List of document dictionaries, each containing 'text' and optional 'metadata'
        index_path: Path where the index will be saved
        test_query: Query string to test searchability (default: "test")
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Dictionary containing:
        {
            "index_path": path to the built index,
            "is_searchable": boolean indicating if index is searchable,
            "test_results_count": number of results from test query
        }
        
    Raises:
        ValueError: If documents list is empty
    """
    if not documents:
        raise ValueError("documents list cannot be empty")
    
    # Build index
    builder = LeannBuilder(backend_name=backend_name)
    
    for doc in documents:
        text = doc.get("text", "")
        if not text or not isinstance(text, str):
            continue
        
        metadata = doc.get("metadata")
        if metadata:
            builder.add_text(text, metadata=metadata)
        else:
            builder.add_text(text)
    
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    
    # Verify searchability
    is_searchable = False
    test_results_count = 0
    
    try:
        searcher = LeannSearcher(index_path=index_path)
        results = searcher.search(test_query, top_k=5)
        is_searchable = True
        test_results_count = len(results)
    except Exception:
        is_searchable = False
    
    return {
        "index_path": index_path,
        "is_searchable": is_searchable,
        "test_results_count": test_results_count
    }
