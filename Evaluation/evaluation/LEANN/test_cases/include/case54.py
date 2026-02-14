# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def get_passage_statistics(
    index_path: str
) -> Dict[str, Any]:
    """Get statistics about passages in an index.
    
    Args:
        index_path: Path to the LEANN index file
        
    Returns:
        Dictionary containing:
        {
            "total_passages": total number of passages,
            "passages_with_metadata": number of passages that have metadata,
            "passages_without_metadata": number of passages without metadata,
            "average_text_length": average length of passage texts
        }
        
    Raises:
        FileNotFoundError: If index metadata file is not found
    """
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
        return {
            "total_passages": 0,
            "passages_with_metadata": 0,
            "passages_without_metadata": 0,
            "average_text_length": 0.0
        }
    
    total_passages = 0
    passages_with_metadata = 0
    total_text_length = 0
    
    with open(passages_path, encoding="utf-8") as f:
        for line in f:
            if not line.strip():
                continue
            passage_data = json.loads(line)
            total_passages += 1
            
            metadata = passage_data.get("metadata", {})
            if metadata:
                passages_with_metadata += 1
            
            text = passage_data.get("text", "")
            total_text_length += len(text)
    
    passages_without_metadata = total_passages - passages_with_metadata
    average_text_length = total_text_length / total_passages if total_passages > 0 else 0.0
    
    return {
        "total_passages": total_passages,
        "passages_with_metadata": passages_with_metadata,
        "passages_without_metadata": passages_without_metadata,
        "average_text_length": average_text_length
    }
