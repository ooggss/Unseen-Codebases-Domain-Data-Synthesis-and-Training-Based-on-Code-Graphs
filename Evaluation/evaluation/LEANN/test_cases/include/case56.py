# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannBuilder
from pathlib import Path


def build_index_with_metadata_template(
    documents: List[Dict[str, Any]],
    index_path: str,
    metadata_template: Dict[str, Any] = None,
    backend_name: str = "hnsw"
) -> str:
    """Build a LEANN index and apply a metadata template to all documents.
    
    Args:
        documents: List of document dictionaries, each containing 'text' and optional 'metadata'
        index_path: Path where the index will be saved
        metadata_template: Optional metadata template to merge with each document's metadata (default: None)
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Path to the built index file
        
    Raises:
        ValueError: If documents list is empty
    """
    if not documents:
        raise ValueError("documents list cannot be empty")
    
    builder = LeannBuilder(backend_name=backend_name)
    
    for doc in documents:
        text = doc.get("text", "")
        if not text or not isinstance(text, str):
            continue
        
        # Merge template metadata with document metadata
        doc_metadata = doc.get("metadata", {})
        if metadata_template:
            merged_metadata = {**metadata_template, **doc_metadata}
        else:
            merged_metadata = doc_metadata
        
        if merged_metadata:
            builder.add_text(text, metadata=merged_metadata)
        else:
            builder.add_text(text)
    
    # Ensure parent directory exists
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    return index_path
