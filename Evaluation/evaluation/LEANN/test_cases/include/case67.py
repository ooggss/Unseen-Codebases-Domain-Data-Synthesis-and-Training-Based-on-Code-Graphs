# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannBuilder
from pathlib import Path


def build_index_with_auto_metadata(
    texts: List[str],
    index_path: str,
    auto_metadata_func: callable = None,
    backend_name: str = "hnsw"
) -> str:
    """Build a LEANN index with automatically generated metadata for each text.
    
    Args:
        texts: List of text strings to index
        index_path: Path where the index will be saved
        auto_metadata_func: Optional function to generate metadata from text.
            Function signature: (text: str, index: int) -> Dict[str, Any]
            If None, no metadata is added
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Path to the built index file
        
    Raises:
        ValueError: If texts list is empty
    """
    if not texts:
        raise ValueError("texts list cannot be empty")
    
    builder = LeannBuilder(backend_name=backend_name)
    
    for i, text in enumerate(texts):
        if not text or not isinstance(text, str):
            continue
        
        if auto_metadata_func:
            metadata = auto_metadata_func(text, i)
            builder.add_text(text, metadata=metadata)
        else:
            builder.add_text(text)
    
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    return index_path
