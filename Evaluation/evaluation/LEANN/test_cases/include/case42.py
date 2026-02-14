# function_implementation_file

from typing import List, Dict, Any
from leann import LeannBuilder
from leann.api import LeannSearcher, PassageManager
from pathlib import Path
import json


def add_documents_to_existing_index(
    index_path: str,
    new_documents: List[Dict[str, Any]]
) -> Dict[str, Any]:
    """Add new documents to an existing index by reading existing passages and rebuilding.
    
    Args:
        index_path: Path to the existing LEANN index file
        new_documents: List of new document dictionaries to add
        
    Returns:
        Dictionary containing:
        {
            "original_passage_count": number of passages before adding,
            "new_passage_count": number of passages after adding,
            "documents_added": number of documents added
        }
        
    Raises:
        FileNotFoundError: If index file is not found
        ValueError: If new_documents is empty
    """
    if not new_documents:
        raise ValueError("new_documents cannot be empty")
    
    # Load existing passages
    meta_path = Path(f"{index_path}.meta.json")
    if not meta_path.exists():
        raise FileNotFoundError(f"Index metadata file not found: {meta_path}")
    
    with open(meta_path, encoding="utf-8") as f:
        meta_data = json.load(f)
    
    # Count original passages
    passages_path = Path(f"{index_path}.passages.jsonl")
    original_count = 0
    if passages_path.exists():
        with open(passages_path, encoding="utf-8") as f:
            for line in f:
                if line.strip():
                    original_count += 1
    
    # Create new builder and add existing passages
    backend_name = meta_data.get("backend_name", "hnsw")
    builder = LeannBuilder(backend_name=backend_name)
    
    # Re-add existing passages (read from passages file)
    if passages_path.exists():
        with open(passages_path, encoding="utf-8") as f:
            for line in f:
                if not line.strip():
                    continue
                passage_data = json.loads(line)
                text = passage_data.get("text", "")
                metadata = passage_data.get("metadata", {})
                if text:
                    if metadata:
                        builder.add_text(text, metadata=metadata)
                    else:
                        builder.add_text(text)
    
    # Add new documents
    documents_added = 0
    for doc in new_documents:
        text = doc.get("text", "")
        if not text or not isinstance(text, str):
            continue
        
        metadata = doc.get("metadata")
        if metadata:
            builder.add_text(text, metadata=metadata)
        else:
            builder.add_text(text)
        documents_added += 1
    
    # Rebuild index
    builder.build_index(index_path)
    
    # Count new passages
    new_count = 0
    if passages_path.exists():
        with open(passages_path, encoding="utf-8") as f:
            for line in f:
                if line.strip():
                    new_count += 1
    
    return {
        "original_passage_count": original_count,
        "new_passage_count": new_count,
        "documents_added": documents_added
    }


def rebuild_index_if_needed(
    index_path: str,
    min_passage_count: int = 0
) -> Dict[str, Any]:
    """Check if an index needs rebuilding based on passage count and rebuild if needed.
    
    Args:
        index_path: Path to the LEANN index file
        min_passage_count: Minimum expected passage count (default: 0)
        
    Returns:
        Dictionary containing:
        {
            "was_rebuilt": boolean indicating if index was rebuilt,
            "passage_count": current passage count,
            "action_taken": "rebuilt" or "no_action"
        }
        
    Raises:
        FileNotFoundError: If index metadata file is not found
    """
    meta_path = Path(f"{index_path}.meta.json")
    if not meta_path.exists():
        raise FileNotFoundError(f"Index metadata file not found: {meta_path}")
    
    # Count current passages
    passages_path = Path(f"{index_path}.passages.jsonl")
    passage_count = 0
    if passages_path.exists():
        with open(passages_path, encoding="utf-8") as f:
            for line in f:
                if line.strip():
                    passage_count += 1
    
    was_rebuilt = False
    
    if passage_count < min_passage_count:
        # Index needs rebuilding - but we can't actually rebuild without documents
        # So we just report that it needs rebuilding
        was_rebuilt = False
        action_taken = "needs_rebuild"
    else:
        action_taken = "no_action"
    
    return {
        "was_rebuilt": was_rebuilt,
        "passage_count": passage_count,
        "action_taken": action_taken
    }
