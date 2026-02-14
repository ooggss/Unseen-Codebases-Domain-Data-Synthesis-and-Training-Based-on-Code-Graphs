
from typing import List, Dict, Any, Optional
from leann.api import PassageManager
from pathlib import Path
import json


def update_passage_metadata_in_memory(
    index_path: str,
    passage_id: str,
    metadata_updates: Dict[str, Any]
) -> Dict[str, Any]:
    """Update metadata for a passage in memory (returns updated passage data without modifying index).
    
    Args:
        index_path: Path to the LEANN index file
        passage_id: ID of the passage to update
        metadata_updates: Dictionary of metadata fields to update/add
        
    Returns:
        Dictionary containing updated passage data
        
    Raises:
        FileNotFoundError: If index metadata file is not found
        KeyError: If passage ID is not found
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
    
    # Get existing passage
    passage_data = passage_manager.get_passage(passage_id)
    
    # Update metadata in memory (create a copy, don't modify original)
    updated_passage = passage_data.copy()
    
    # Merge metadata updates
    if "metadata" not in updated_passage:
        updated_passage["metadata"] = {}
    
    if not isinstance(updated_passage["metadata"], dict):
        updated_passage["metadata"] = {}
    
    updated_passage["metadata"].update(metadata_updates)
    
    return updated_passage
