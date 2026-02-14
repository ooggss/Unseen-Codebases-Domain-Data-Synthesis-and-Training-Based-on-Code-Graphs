# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def get_passages_by_text_length(
    index_path: str,
    min_length: int = 0,
    max_length: int = None
) -> List[Dict[str, Any]]:
    """Retrieve passages from an index filtered by text length.
    
    Args:
        index_path: Path to the LEANN index file
        min_length: Minimum text length in characters (default: 0)
        max_length: Maximum text length in characters (default: None, no upper limit)
        
    Returns:
        List of passage dictionaries with text length within the specified range
        
    Raises:
        FileNotFoundError: If index metadata file is not found
        ValueError: If min_length < 0 or max_length < min_length
    """
    if min_length < 0:
        raise ValueError("min_length must be non-negative")
    
    if max_length is not None and max_length < min_length:
        raise ValueError("max_length must be >= min_length")
    
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
            
            text = passage_data.get("text", "")
            text_length = len(text)
            
            if text_length >= min_length:
                if max_length is None or text_length <= max_length:
                    matching_passages.append(passage_data)
    
    return matching_passages
