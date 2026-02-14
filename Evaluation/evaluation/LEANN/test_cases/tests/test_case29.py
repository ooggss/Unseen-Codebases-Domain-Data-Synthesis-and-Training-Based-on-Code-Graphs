# new_test_case_file

import pytest
from pathlib import Path
from case29 import get_all_passages_with_metadata
from leann.api import LeannBuilder
import shutil


def test_get_all_passages_with_metadata(tmp_path):
    """Test retrieving passages with required metadata fields."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Content with all fields", metadata={"category": "tech", "rating": 5, "author": "John"})
    builder.add_text("Content missing field", metadata={"category": "tech", "rating": 4})
    builder.add_text("Content with all fields 2", metadata={"category": "web", "rating": 5, "author": "Jane"})
    builder.build_index(index_path)
    
    passages = get_all_passages_with_metadata(index_path, ["category", "rating", "author"])
    
    assert len(passages) >= 2, "Should find passages with all required fields"
    assert all("category" in p.get("metadata", {}) for p in passages), "All passages should have category"
    assert all("rating" in p.get("metadata", {}) for p in passages), "All passages should have rating"
    assert all("author" in p.get("metadata", {}) for p in passages), "All passages should have author"


def test_get_all_passages_with_metadata_empty_fields():
    """Test with empty required fields should raise ValueError."""
    with pytest.raises(ValueError, match="cannot be empty"):
        get_all_passages_with_metadata("/tmp/test.leann", [])
