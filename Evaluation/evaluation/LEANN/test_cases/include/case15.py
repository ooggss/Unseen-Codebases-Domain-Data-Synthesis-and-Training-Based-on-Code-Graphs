# function_implementation_file

from typing import List, Dict, Any, Optional
from leann.api import PassageManager
from pathlib import Path
import json


def batch_get_passages(
    index_path: str,
    passage_ids: List[str]
) -> Dict[str, Dict[str, Any]]:
    """Retrieve multiple passages by their IDs from a LEANN index.
    
    Args:
        index_path: Path to the LEANN index file
        passage_ids: List of passage IDs to retrieve
        
    Returns:
        Dictionary mapping passage_id to passage data (id, text, metadata).
        Missing passages will have None as value.
        
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
    
    # Batch retrieve passages
    results = {}
    for passage_id in passage_ids:
        try:
            passage_data = passage_manager.get_passage(passage_id)
            results[passage_id] = passage_data
        except KeyError:
            # Passage not found, set to None
            results[passage_id] = None
    
    return results

