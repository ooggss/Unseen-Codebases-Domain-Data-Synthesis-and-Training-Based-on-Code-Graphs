# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannBuilder, LeannSearcher
from pathlib import Path


def create_index_from_dict(
    data_dict: Dict[str, str],
    index_path: str,
    backend_name: str = "hnsw"
) -> str:
    """Build a LEANN index from a dictionary mapping keys to text values.
    
    Args:
        data_dict: Dictionary mapping keys to text strings
        index_path: Path where the index will be saved
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Path to the built index file
        
    Raises:
        ValueError: If data_dict is empty
    """
    if not data_dict:
        raise ValueError("data_dict cannot be empty")
    
    builder = LeannBuilder(backend_name=backend_name)
    
    for key, text in data_dict.items():
        if not text or not isinstance(text, str):
            continue
        
        # Use key as metadata
        builder.add_text(text, metadata={"key": key})
    
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    return index_path
