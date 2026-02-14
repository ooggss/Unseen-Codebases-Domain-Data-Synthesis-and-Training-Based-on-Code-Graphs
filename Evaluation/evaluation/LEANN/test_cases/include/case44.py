# function_implementation_file

from typing import List, Dict, Any
from leann.api import PassageManager, LeannSearcher
from pathlib import Path
import json
from collections import Counter, defaultdict


def get_index_statistics(
    index_path: str
) -> Dict[str, Any]:
    """Get comprehensive statistics about a LEANN index.
    
    Args:
        index_path: Path to the LEANN index file
        
    Returns:
        Dictionary containing:
        {
            "total_passages": total number of passages,
            "metadata_fields": list of unique metadata field names,
            "field_value_counts": dictionary of field value counts
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
    total_passages = 0
    all_metadata_fields = set()
    field_value_counts = defaultdict(Counter)
    
    if passages_path.exists():
        with open(passages_path, encoding="utf-8") as f:
            for line in f:
                if not line.strip():
                    continue
                passage_data = json.loads(line)
                total_passages += 1
                
                metadata = passage_data.get("metadata", {})
                for field_name, field_value in metadata.items():
                    all_metadata_fields.add(field_name)
                    field_value_counts[field_name][field_value] += 1
    
    return {
        "total_passages": total_passages,
        "metadata_fields": list(all_metadata_fields),
        "field_value_counts": {k: dict(v) for k, v in field_value_counts.items()}
    }


def analyze_index_coverage(
    index_path: str,
    required_fields: List[str]
) -> Dict[str, Any]:
    """Analyze how well an index covers required metadata fields.
    
    Args:
        index_path: Path to the LEANN index file
        required_fields: List of metadata field names that should be present
        
    Returns:
        Dictionary containing:
        {
            "coverage_percentage": percentage of passages that have all required fields,
            "field_coverage": dictionary mapping field name to coverage percentage,
            "missing_fields": list of required fields not found in any passage
        }
        
    Raises:
        FileNotFoundError: If index metadata file is not found
    """
    stats = get_index_statistics(index_path)
    total_passages = stats["total_passages"]
    
    if total_passages == 0:
        return {
            "coverage_percentage": 0.0,
            "field_coverage": {field: 0.0 for field in required_fields},
            "missing_fields": required_fields
        }
    
    # Count passages with all required fields
    meta_path = Path(f"{index_path}.meta.json")
    with open(meta_path, encoding="utf-8") as f:
        meta_data = json.load(f)
    
    passage_sources = meta_data.get("passage_sources", [])
    passage_manager = PassageManager(passage_sources, metadata_file_path=str(meta_path))
    
    passages_path = Path(f"{index_path}.passages.jsonl")
    passages_with_all_fields = 0
    field_counts = {field: 0 for field in required_fields}
    
    if passages_path.exists():
        with open(passages_path, encoding="utf-8") as f:
            for line in f:
                if not line.strip():
                    continue
                passage_data = json.loads(line)
                metadata = passage_data.get("metadata", {})
                
                has_all = all(field in metadata for field in required_fields)
                if has_all:
                    passages_with_all_fields += 1
                
                for field in required_fields:
                    if field in metadata:
                        field_counts[field] += 1
    
    coverage_percentage = (passages_with_all_fields / total_passages * 100) if total_passages > 0 else 0.0
    field_coverage = {field: (count / total_passages * 100) if total_passages > 0 else 0.0 
                     for field, count in field_counts.items()}
    missing_fields = [field for field in required_fields if field_counts[field] == 0]
    
    return {
        "coverage_percentage": coverage_percentage,
        "field_coverage": field_coverage,
        "missing_fields": missing_fields
    }
