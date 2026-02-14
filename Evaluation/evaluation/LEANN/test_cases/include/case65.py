# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannBuilder, LeannSearcher
from pathlib import Path


def build_index_and_search(
    documents: List[Dict[str, Any]],
    index_path: str,
    query: str,
    top_k: int = 5,
    backend_name: str = "hnsw"
) -> List[Any]:
    """Build an index and immediately perform a search on it.
    
    Args:
        documents: List of document dictionaries, each containing 'text' and optional 'metadata'
        index_path: Path where the index will be saved
        query: Search query string
        top_k: Number of results to retrieve (default: 5)
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        List of SearchResult objects from the search
        
    Raises:
        ValueError: If documents list is empty or query is empty
    """
    if not documents:
        raise ValueError("documents list cannot be empty")
    
    if not query or not query.strip():
        raise ValueError("query cannot be empty")
    
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
    
    # Search
    searcher = LeannSearcher(index_path=index_path)
    results = searcher.search(query, top_k=top_k)
    
    return results
