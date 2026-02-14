# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager
from pathlib import Path
import json


def export_index_metadata(
    index_path: str,
    output_file: str
) -> Dict[str, Any]:
    """Export index metadata and passage information to a JSON file.
    
    Args:
        index_path: Path to the LEANN index file
        output_file: Path where the exported data will be saved
        
    Returns:
        Dictionary containing:
        {
            "exported_passages": number of passages exported,
            "output_file": path to the output file,
            "status": "success" or "failed"
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
    
    # Load passages
    passages_path = Path(f"{index_path}.passages.jsonl")
    exported_passages = []
    
    if passages_path.exists():
        with open(passages_path, encoding="utf-8") as f:
            for line in f:
                if not line.strip():
                    continue
                passage_data = json.loads(line)
                exported_passages.append(passage_data)
    
    # Export to JSON
    export_data = {
        "index_metadata": meta_data,
        "passages": exported_passages
    }
    
    output_path = Path(output_file)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    
    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(export_data, f, indent=2, ensure_ascii=False)
    
    return {
        "exported_passages": len(exported_passages),
        "output_file": output_file,
        "status": "success"
    }


def import_index_from_metadata(
    export_file: str,
    index_path: str,
    backend_name: str = "hnsw"
) -> Dict[str, Any]:
    """Import and rebuild an index from exported metadata and passages.
    
    Args:
        export_file: Path to the exported JSON file
        index_path: Path where the new index will be saved
        backend_name: Backend name for the new index (default: "hnsw")
        
    Returns:
        Dictionary containing:
        {
            "index_path": path to the built index,
            "passages_imported": number of passages imported,
            "status": "success" or "failed"
        }
        
    Raises:
        FileNotFoundError: If export file is not found
        ValueError: If export file format is invalid
    """
    export_path = Path(export_file)
    if not export_path.exists():
        raise FileNotFoundError(f"Export file not found: {export_file}")
    
    with open(export_path, encoding="utf-8") as f:
        export_data = json.load(f)
    
    if "passages" not in export_data:
        raise ValueError("Export file must contain 'passages' key")
    
    passages = export_data["passages"]
    
    # Build new index from exported passages
    from leann import LeannBuilder
    builder = LeannBuilder(backend_name=backend_name)
    
    passages_imported = 0
    for passage_data in passages:
        text = passage_data.get("text", "")
        if not text:
            continue
        
        metadata = passage_data.get("metadata", {})
        if metadata:
            builder.add_text(text, metadata=metadata)
        else:
            builder.add_text(text)
        passages_imported += 1
    
    # Ensure parent directory exists
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    
    return {
        "index_path": index_path,
        "passages_imported": passages_imported,
        "status": "success"
    }
