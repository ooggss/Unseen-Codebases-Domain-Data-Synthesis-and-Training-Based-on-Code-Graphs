# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def get_all_passages_with_metadata(
    index_path: str,
    required_metadata_fields: List[str]
) -> List[Dict[str, Any]]:
    """Retrieve all passages from an index that contain all specified metadata fields.
    
    Args:
        index_path: Path to the LEANN index file
        required_metadata_fields: List of metadata field names that must be present in each passage
        
    Returns:
        List of passage dictionaries that contain all required metadata fields
        
    Raises:
        FileNotFoundError: If index metadata file is not found
        ValueError: If required_metadata_fields is empty
    """
    if not required_metadata_fields:
        raise ValueError("required_metadata_fields cannot be empty")
    
    # Load metadata to get passage sources
    meta_path = Path(f"{index_path}.meta.json")
    if not meta_path.exists():
        raise FileNotFoundError(f"Index metadata file not found: {meta_path}")
    
    with open(meta_path, encoding="utf-8") as f:
        meta_data = json.load(f)
    
    # Create PassageManager
    passage_sources = meta_data.get("passage_sources", [])
    passage_manager = PassageManager(passage_sources, metadata_file_path=str(meta_path))
    
    # Load passages file
    passages_path = Path(f"{index_path}.passages.jsonl")
    if not passages_path.exists():
        return []
    
    matching_passages = []
    
    # Read all passages from JSONL file
    with open(passages_path, encoding="utf-8") as f:
        for line in f:
            if not line.strip():
                continue
            passage_data = json.loads(line)
            
            # Check if all required fields are present
            passage_metadata = passage_data.get("metadata", {})
            has_all_fields = all(field in passage_metadata for field in required_metadata_fields)
            
            if has_all_fields:
                matching_passages.append(passage_data)
    
    return matching_passages
