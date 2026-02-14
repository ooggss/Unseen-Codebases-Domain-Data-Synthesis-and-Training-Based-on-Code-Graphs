# function_implementation_file

from typing import List, Dict, Any, Optional
from leann import LeannBuilder
from leann.api import LeannSearcher, SearchResult
from pathlib import Path


def build_multiple_indexes(
    index_configs: List[Dict[str, Any]],
    base_dir: str
) -> Dict[str, str]:
    """Build multiple LEANN indexes from different document sources.
    
    Args:
        index_configs: List of index configuration dictionaries, each containing:
            - 'index_name': Name of the index
            - 'documents': List of documents with 'text' and optional 'metadata'
            - 'backend_name': Optional backend name (default: 'hnsw')
        base_dir: Base directory where all indexes will be stored
        
    Returns:
        Dictionary mapping index_name to index_path for each successfully built index
        
    Raises:
        ValueError: If index_configs is empty or if index_name is missing
    """
    if not index_configs:
        raise ValueError("index_configs cannot be empty")
    
    base_path = Path(base_dir)
    base_path.mkdir(parents=True, exist_ok=True)
    
    index_paths = {}
    
    for config in index_configs:
        if 'index_name' not in config:
            raise ValueError("Each config must have 'index_name'")
        if 'documents' not in config:
            raise ValueError("Each config must have 'documents'")
        
        index_name = config['index_name']
        documents = config['documents']
        backend_name = config.get('backend_name', 'hnsw')
        
        # Create index path (ensure absolute path)
        index_path_obj = (base_path / f"{index_name}.leann").resolve()
        index_path = str(index_path_obj)
        
        # Ensure parent directory exists
        index_path_obj.parent.mkdir(parents=True, exist_ok=True)
        
        # Build the index
        builder = LeannBuilder(backend_name=backend_name)
        
        for doc in documents:
            text = doc.get('text', '')
            if not text:
                continue  # Skip empty texts
            metadata = doc.get('metadata')
            if metadata:
                builder.add_text(text, metadata=metadata)
            else:
                builder.add_text(text)
        
        # Build index - this creates multiple files (.leann, .meta.json, .passages.jsonl, etc.)
        builder.build_index(index_path)
        index_paths[index_name] = index_path
    
    return index_paths


def unified_search_across_indexes(
    index_paths: Dict[str, str],
    query: str,
    top_k_per_index: int = 3,
    global_top_k: Optional[int] = None
) -> List[SearchResult]:
    """Search across multiple indexes and return unified, deduplicated results.
    
    Args:
        index_paths: Dictionary mapping index_name to index_path
        query: Search query string
        top_k_per_index: Number of results to retrieve from each index (default: 3)
        global_top_k: Optional limit on total results after merging (default: None, returns all)
        
    Returns:
        List of SearchResult objects, sorted by score (descending), deduplicated by text content
    """
    all_results = []
    seen_texts = set()
    
    # Search each index
    for index_name, index_path in index_paths.items():
        try:
            searcher = LeannSearcher(index_path=index_path)
            results = searcher.search(query, top_k=top_k_per_index)
            
            # Add index_name to metadata for tracking
            for result in results:
                # Deduplicate by text content
                if result.text not in seen_texts:
                    seen_texts.add(result.text)
                    # Add source index to metadata
                    if result.metadata is None:
                        result.metadata = {}
                    result.metadata['source_index'] = index_name
                    all_results.append(result)
        except Exception:
            # If one index fails, continue with others
            continue
    
    # Sort by score (descending)
    all_results.sort(key=lambda x: x.score, reverse=True)
    
    # Apply global_top_k if specified
    if global_top_k is not None:
        all_results = all_results[:global_top_k]
    
    return all_results
