# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def find_passages_by_text_pattern(
    index_path: str,
    pattern: str,
    case_sensitive: bool = False
) -> List[Dict[str, Any]]:
    """Find all passages in an index whose text contains a specified pattern.
    
    Args:
        index_path: Path to the LEANN index file
        pattern: Text pattern to search for (substring match)
        case_sensitive: Whether the search should be case-sensitive (default: False)
        
    Returns:
        List of passage dictionaries whose text contains the pattern
        
    Raises:
        FileNotFoundError: If index metadata file is not found
        ValueError: If pattern is empty
    """
    if not pattern:
        raise ValueError("pattern cannot be empty")
    
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
            
            # Check if text contains pattern
            passage_text = passage_data.get("text", "")
            if case_sensitive:
                matches = pattern in passage_text
            else:
                matches = pattern.lower() in passage_text.lower()
            
            if matches:
                matching_passages.append(passage_data)
    
    return matching_passages
