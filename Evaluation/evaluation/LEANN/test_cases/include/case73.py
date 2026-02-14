# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def get_passages_by_multiple_criteria(
    index_path: str,
    criteria: Dict[str, Any]
) -> List[Dict[str, Any]]:
    """Retrieve passages from an index that match multiple metadata criteria (AND logic).
    
    Args:
        index_path: Path to the LEANN index file
        criteria: Dictionary of metadata field-value pairs that must all match
        
    Returns:
        List of passage dictionaries that match all criteria
        
    Raises:
        FileNotFoundError: If index metadata file is not found
    """
    meta_path = Path(f"{index_path}.meta.json")
    if not meta_path.exists():
        raise FileNotFoundError(f"Index metadata file not found: {meta_path}")
    
    with open(meta_path, encoding="utf-8") as f:
        meta_data = json.load(f)
    
    passage_sources = meta_data.get("passage_sources", [])
    passage_manager = PassageManager(passage_sources, metadata_file_path=str(meta_path))
    
    passages_path = Path(f"{index_path}.passages.jsonl")
    if not passages_path.exists():
        return []
    
    matching_passages = []
    
    with open(passages_path, encoding="utf-8") as f:
        for line in f:
            if not line.strip():
                continue
            passage_data = json.loads(line)
            
            passage_metadata = passage_data.get("metadata", {})
            matches_all = True
            
            for field_name, expected_value in criteria.items():
                if field_name not in passage_metadata or passage_metadata[field_name] != expected_value:
                    matches_all = False
                    break
            
            if matches_all:
                matching_passages.append(passage_data)
    
    return matching_passages
