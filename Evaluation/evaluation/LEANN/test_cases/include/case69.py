# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def get_passages_by_metadata_list(
    index_path: str,
    field_name: str,
    allowed_values: List[Any]
) -> List[Dict[str, Any]]:
    """Retrieve passages from an index where a metadata field matches any value in a list.
    
    Args:
        index_path: Path to the LEANN index file
        field_name: Metadata field name to filter by
        allowed_values: List of field values to match (passages matching any value will be returned)
        
    Returns:
        List of passage dictionaries that have the field matching any value in allowed_values
        
    Raises:
        FileNotFoundError: If index metadata file is not found
        ValueError: If allowed_values is empty
    """
    if not allowed_values:
        raise ValueError("allowed_values cannot be empty")
    
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
    
    allowed_set = set(allowed_values)
    matching_passages = []
    
    with open(passages_path, encoding="utf-8") as f:
        for line in f:
            if not line.strip():
                continue
            passage_data = json.loads(line)
            
            passage_metadata = passage_data.get("metadata", {})
            field_value = passage_metadata.get(field_name)
            
            if field_value in allowed_set:
                matching_passages.append(passage_data)
    
    return matching_passages
