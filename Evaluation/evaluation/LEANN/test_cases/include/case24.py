# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def get_passages_by_metadata_range(
    index_path: str,
    field_name: str,
    min_value: float,
    max_value: float
) -> List[Dict[str, Any]]:
    """Retrieve all passages from an index where a numeric metadata field falls within a specified range.
    
    Args:
        index_path: Path to the LEANN index file
        field_name: Name of the numeric metadata field to filter by
        min_value: Minimum value (inclusive)
        max_value: Maximum value (inclusive)
        
    Returns:
        List of passage dictionaries that have the field within the specified range
        
    Raises:
        FileNotFoundError: If index metadata file is not found
        ValueError: If min_value > max_value
    """
    if min_value > max_value:
        raise ValueError("min_value must be less than or equal to max_value")
    
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
            
            # Check if field exists and is within range
            passage_metadata = passage_data.get("metadata", {})
            field_value = passage_metadata.get(field_name)
            
            if field_value is not None:
                try:
                    numeric_value = float(field_value)
                    if min_value <= numeric_value <= max_value:
                        matching_passages.append(passage_data)
                except (ValueError, TypeError):
                    # Skip non-numeric values
                    continue
    
    return matching_passages
