# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannBuilder
from pathlib import Path


def build_index_from_text_list(
    texts: List[str],
    index_path: str,
    metadata_list: List[Dict[str, Any]] = None,
    backend_name: str = "hnsw"
) -> str:
    """Build a LEANN index from a simple list of text strings.
    
    Args:
        texts: List of text strings to index
        index_path: Path where the index will be saved
        metadata_list: Optional list of metadata dictionaries, one per text (default: None)
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Path to the built index file
        
    Raises:
        ValueError: If texts list is empty or if metadata_list length doesn't match texts length
    """
    if not texts:
        raise ValueError("texts list cannot be empty")
    
    if metadata_list is not None and len(metadata_list) != len(texts):
        raise ValueError("metadata_list length must match texts length")
    
    builder = LeannBuilder(backend_name=backend_name)
    
    for i, text in enumerate(texts):
        if not text or not isinstance(text, str):
            continue  # Skip empty texts
        
        if metadata_list:
            metadata = metadata_list[i]
            builder.add_text(text, metadata=metadata)
        else:
            builder.add_text(text)
    
    # Ensure parent directory exists
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    return index_path
