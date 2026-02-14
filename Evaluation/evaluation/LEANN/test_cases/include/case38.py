# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannBuilder
from pathlib import Path


def build_index_with_metadata_validation(
    documents: List[Dict[str, Any]],
    index_path: str,
    required_metadata_fields: List[str] = None,
    backend_name: str = "hnsw"
) -> str:
    """Build a LEANN index with validation of required metadata fields.
    
    Args:
        documents: List of document dictionaries, each containing 'text' and optional 'metadata'
        index_path: Path where the index will be saved
        required_metadata_fields: Optional list of metadata field names that must be present in all documents (default: None)
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Path to the built index file
        
    Raises:
        ValueError: If documents list is empty or if required fields are missing
    """
    if not documents:
        raise ValueError("documents list cannot be empty")
    
    if required_metadata_fields is None:
        required_metadata_fields = []
    
    builder = LeannBuilder(backend_name=backend_name)
    
    for i, doc in enumerate(documents):
        text = doc.get("text", "")
        if not text or not isinstance(text, str):
            continue
        
        metadata = doc.get("metadata", {})
        
        # Validate required fields
        if required_metadata_fields:
            missing_fields = [field for field in required_metadata_fields if field not in metadata]
            if missing_fields:
                raise ValueError(f"Document {i} missing required metadata fields: {missing_fields}")
        
        if metadata:
            builder.add_text(text, metadata=metadata)
        else:
            builder.add_text(text)
    
    # Ensure parent directory exists
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    return index_path
