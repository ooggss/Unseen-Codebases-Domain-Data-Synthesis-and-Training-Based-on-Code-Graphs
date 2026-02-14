# function_implementation_file

from typing import List, Dict, Any
from leann.api import LeannBuilder
from pathlib import Path


def build_index_from_text_file(
    text_file_path: str,
    index_path: str,
    metadata: Dict[str, Any] = None,
    backend_name: str = "hnsw"
) -> str:
    """Build a LEANN index from a single text file.
    
    Args:
        text_file_path: Path to the text file to index
        index_path: Path where the index will be saved
        metadata: Optional metadata to attach to all passages from this file (default: None)
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Path to the built index file
        
    Raises:
        FileNotFoundError: If text file is not found
        ValueError: If text file is empty
    """
    text_path = Path(text_file_path)
    if not text_path.exists():
        raise FileNotFoundError(f"Text file not found: {text_file_path}")
    
    text_content = text_path.read_text(encoding="utf-8")
    if not text_content.strip():
        raise ValueError("Text file is empty")
    
    builder = LeannBuilder(backend_name=backend_name)
    
    # Add text with optional metadata
    if metadata:
        builder.add_text(text_content, metadata=metadata)
    else:
        builder.add_text(text_content)
    
    # Ensure parent directory exists
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    return index_path
