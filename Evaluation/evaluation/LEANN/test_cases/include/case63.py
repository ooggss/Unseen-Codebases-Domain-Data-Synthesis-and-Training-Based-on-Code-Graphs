# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def get_passages_by_text_contains(
    index_path: str,
    search_text: str,
    case_sensitive: bool = False
) -> List[Dict[str, Any]]:
    """Retrieve passages from an index whose text contains a specific substring.
    
    Args:
        index_path: Path to the LEANN index file
        search_text: Substring to search for in passage texts
        case_sensitive: Whether the search should be case-sensitive (default: False)
        
    Returns:
        List of passage dictionaries whose text contains the search_text
        
    Raises:
        FileNotFoundError: If index metadata file is not found
        ValueError: If search_text is empty
    """
    if not search_text:
        raise ValueError("search_text cannot be empty")
    
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
            if case_sensitive:
                matches = search_text in text
            else:
                matches = search_text.lower() in text.lower()
            
            if matches:
                matching_passages.append(passage_data)
    
    return matching_passages
