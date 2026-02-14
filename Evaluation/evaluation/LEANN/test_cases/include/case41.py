# function_implementation_file

from typing import List, Dict, Any, Optional
from leann import LeannBuilder
from leann.api import LeannSearcher, PassageManager
from pathlib import Path
import json


def build_and_validate_index(
    documents: List[Dict[str, Any]],
    index_path: str,
    backend_name: str = "hnsw"
) -> Dict[str, Any]:
    """Build a LEANN index and return validation information.
    
    Args:
        documents: List of document dictionaries, each containing 'text' and optional 'metadata'
        index_path: Path where the index will be saved
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Dictionary containing:
        {
            "index_path": path to the built index,
            "document_count": number of documents indexed,
            "status": "success" or "failed"
        }
        
    Raises:
        ValueError: If documents list is empty
    """
    if not documents:
        raise ValueError("documents list cannot be empty")
    
    builder = LeannBuilder(backend_name=backend_name)
    doc_count = 0
    
    for doc in documents:
        text = doc.get("text", "")
        if not text or not isinstance(text, str):
            continue
        
        metadata = doc.get("metadata")
        if metadata:
            builder.add_text(text, metadata=metadata)
        else:
            builder.add_text(text)
        doc_count += 1
    
    # Ensure parent directory exists
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    
    return {
        "index_path": index_path,
        "document_count": doc_count,
        "status": "success"
    }


def verify_index_integrity(
    index_path: str
) -> Dict[str, Any]:
    """Verify the integrity of a built LEANN index.
    
    Args:
        index_path: Path to the LEANN index file
        
    Returns:
        Dictionary containing:
        {
            "is_valid": boolean indicating if index is valid,
            "passage_count": number of passages in the index,
            "metadata_file_exists": whether metadata file exists,
            "errors": list of error messages if any
        }
        
    Raises:
        FileNotFoundError: If index metadata file is not found
    """
    meta_path = Path(f"{index_path}.meta.json")
    if not meta_path.exists():
        raise FileNotFoundError(f"Index metadata file not found: {meta_path}")
    
    errors = []
    passage_count = 0
    
    try:
        with open(meta_path, encoding="utf-8") as f:
            meta_data = json.load(f)
        
        # Create PassageManager to verify passages
        passage_sources = meta_data.get("passage_sources", [])
        passage_manager = PassageManager(passage_sources, metadata_file_path=str(meta_path))
        
        # Count passages
        passages_path = Path(f"{index_path}.passages.jsonl")
        if passages_path.exists():
            with open(passages_path, encoding="utf-8") as f:
                for line in f:
                    if line.strip():
                        passage_count += 1
        else:
            errors.append("Passages file not found")
        
        # Try to create searcher to verify index is searchable
        try:
            searcher = LeannSearcher(index_path=index_path)
        except Exception as e:
            errors.append(f"Cannot create searcher: {str(e)}")
        
    except Exception as e:
        errors.append(f"Error reading index: {str(e)}")
    
    is_valid = len(errors) == 0 and passage_count > 0
    
    return {
        "is_valid": is_valid,
        "passage_count": passage_count,
        "metadata_file_exists": meta_path.exists(),
        "errors": errors
    }
