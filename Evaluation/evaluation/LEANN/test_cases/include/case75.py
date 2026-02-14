# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannBuilder, LeannSearcher
from pathlib import Path


def build_index_with_validation_and_search(
    documents: List[Dict[str, Any]],
    index_path: str,
    validation_query: str,
    expected_min_results: int = 1,
    backend_name: str = "hnsw"
) -> Dict[str, Any]:
    """Build an index, validate it by searching, and return build and validation results.
    
    Args:
        documents: List of document dictionaries, each containing 'text' and optional 'metadata'
        index_path: Path where the index will be saved
        validation_query: Query string to use for validation search
        expected_min_results: Minimum number of results expected from validation query (default: 1)
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Dictionary containing:
        {
            "index_path": path to the built index,
            "build_success": boolean indicating if build succeeded,
            "validation_success": boolean indicating if validation passed,
            "validation_results_count": number of results from validation query
        }
        
    Raises:
        ValueError: If documents list is empty
    """
    if not documents:
        raise ValueError("documents list cannot be empty")
    
    build_success = False
    validation_success = False
    validation_results_count = 0
    
    try:
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
        build_success = True
        
        # Validate by searching
        searcher = LeannSearcher(index_path=index_path)
        results = searcher.search(validation_query, top_k=10)
        validation_results_count = len(results)
        validation_success = validation_results_count >= expected_min_results
        
    except Exception:
        build_success = False
        validation_success = False
    
    return {
        "index_path": index_path,
        "build_success": build_success,
        "validation_success": validation_success,
        "validation_results_count": validation_results_count
    }
