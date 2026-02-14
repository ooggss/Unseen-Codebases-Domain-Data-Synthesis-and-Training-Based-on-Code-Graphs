# new_test_case_file

import pytest
from pathlib import Path
from case40 import get_passages_by_field_values
from leann.api import LeannBuilder
import shutil


def test_get_passages_by_field_values(tmp_path):
    """Test retrieving passages by field values."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "language": "python"})
    builder.add_text("JavaScript guide", metadata={"category": "tech", "language": "javascript"})
    builder.add_text("Web design", metadata={"category": "web", "language": "html"})
    builder.build_index(index_path)
    
    passages = get_passages_by_field_values(index_path, "category", ["tech", "web"])
    
    assert len(passages) >= 2, "Should find passages matching field values"
    assert all(p.get("metadata", {}).get("category") in ["tech", "web"] for p in passages), \
        "All passages should have category in the specified values"


def test_get_passages_by_field_values_empty():
    """Test with empty field_values should raise ValueError."""
    with pytest.raises(ValueError, match="field_values cannot be empty"):
        get_passages_by_field_values("/tmp/test.leann", "category", [])
