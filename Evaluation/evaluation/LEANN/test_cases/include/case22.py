# function_implementation_file

from typing import List, Dict, Any, Optional
from leann.api import LeannBuilder
from pathlib import Path
import json


def build_index_from_json_documents(
    json_file_path: str,
    index_path: str,
    text_field: str = "text",
    metadata_fields: Optional[List[str]] = None,
    backend_name: str = "hnsw"
) -> str:
    """Build a LEANN index from a JSON file containing documents.
    
    Args:
        json_file_path: Path to JSON file containing list of documents
        index_path: Path where the index will be saved
        text_field: Name of the field containing the text content (default: "text")
        metadata_fields: Optional list of field names to include as metadata (default: None, includes all except text_field)
        backend_name: Backend name for the index (default: "hnsw")
        
    Returns:
        Path to the built index file
        
    Raises:
        FileNotFoundError: If JSON file is not found
        ValueError: If JSON file is invalid or text_field is missing in documents
    """
    json_path = Path(json_file_path)
    if not json_path.exists():
        raise FileNotFoundError(f"JSON file not found: {json_file_path}")
    
    with open(json_path, encoding="utf-8") as f:
        documents = json.load(f)
    
    if not isinstance(documents, list):
        raise ValueError("JSON file must contain a list of documents")
    
    if not documents:
        raise ValueError("JSON file must contain at least one document")
    
    builder = LeannBuilder(backend_name=backend_name)
    
    for doc in documents:
        if text_field not in doc:
            raise ValueError(f"Document missing required field '{text_field}': {doc}")
        
        text = doc[text_field]
        if not isinstance(text, str) or not text.strip():
            continue  # Skip empty texts
        
        # Extract metadata
        metadata = {}
        if metadata_fields is None:
            # Include all fields except text_field
            metadata = {k: v for k, v in doc.items() if k != text_field}
        else:
            # Include only specified metadata fields
            for field in metadata_fields:
                if field in doc and field != text_field:
                    metadata[field] = doc[field]
        
        if metadata:
            builder.add_text(text, metadata=metadata)
        else:
            builder.add_text(text)
    
    # Ensure parent directory exists
    index_path_obj = Path(index_path)
    index_path_obj.parent.mkdir(parents=True, exist_ok=True)
    
    builder.build_index(index_path)
    return index_path
