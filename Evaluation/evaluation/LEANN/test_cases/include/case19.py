
from typing import List, Dict, Any, Optional
from leann.api import PassageManager
from pathlib import Path
import json

def filter_passages_by_metadata_criteria(
    index_path: str,
    metadata_criteria: Dict[str, Any]
) -> List[Dict[str, Any]]:
    """Retrieve all passages from an index that match metadata criteria.
    
    Args:
        index_path: Path to the LEANN index file
        metadata_criteria: Dictionary of metadata field-value pairs to match.
            Example: {"category": "tech", "rating": 5.0}
            All criteria must match (AND logic)
        
    Returns:
        List of passage dictionaries that match all criteria
        
    Raises:
        FileNotFoundError: If index metadata file is not found
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
    
    # Load passages file to get all passage IDs
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
            
            # Check if metadata matches all criteria
            passage_metadata = passage_data.get("metadata", {})
            matches = True
            
            for key, value in metadata_criteria.items():
                if key not in passage_metadata or passage_metadata[key] != value:
                    matches = False
                    break
            
            if matches:
                matching_passages.append(passage_data)
    
    return matching_passages