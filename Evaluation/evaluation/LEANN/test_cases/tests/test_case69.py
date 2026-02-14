# new_test_case_file

import pytest
from pathlib import Path
from case69 import get_passages_by_metadata_list
from leann.api import LeannBuilder
import shutil


def test_get_passages_by_metadata_list(tmp_path):
    """Test retrieving passages by metadata list."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "language": "python"})
    builder.add_text("JavaScript guide", metadata={"category": "tech", "language": "javascript"})
    builder.add_text("Web design", metadata={"category": "web", "language": "html"})
    builder.build_index(index_path)
    
    passages = get_passages_by_metadata_list(index_path, "category", ["tech", "web"])
    
    assert len(passages) >= 2, "Should find passages matching values"
    assert all(p.get("metadata", {}).get("category") in ["tech", "web"] for p in passages), \
        "All passages should have category in allowed values"


def test_get_passages_by_metadata_list_empty():
    """Test with empty allowed_values should raise ValueError."""
    with pytest.raises(ValueError, match="allowed_values cannot be empty"):
        get_passages_by_metadata_list("/tmp/test.leann", "category", [])
