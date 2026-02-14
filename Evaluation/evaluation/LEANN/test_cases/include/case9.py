# function_implementation_file

from typing import Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def get_passage_by_id(index_path: str, passage_id: str) -> Dict[str, Any]:
    """Retrieve a passage by its ID from a LEANN index.
    
    Args:
        index_path: Path to the LEANN index file
        passage_id: ID of the passage to retrieve
        
    Returns:
        Dictionary containing passage data (id, text, metadata)
        
    Raises:
        KeyError: If passage ID is not found
        FileNotFoundError: If index files are not found
    """
    # Load metadata to get passage sources
    meta_path = Path(f"{index_path}.meta.json")
    if not meta_path.exists():
        raise FileNotFoundError(f"Index metadata file not found: {meta_path}")
    
    with open(meta_path, encoding="utf-8") as f:
        meta_data = json.load(f)
    
    # Create PassageManager
    passage_sources = meta_data.get("passage_sources", [])
    passage_manager = PassageManager(passage_sources, metadata_file_path=str(meta_path))
    
    # Get passage by ID
    passage_data = passage_manager.get_passage(passage_id)
    
    return passage_data

