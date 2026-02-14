# new_test_case_file

import pytest
from pathlib import Path
from case9 import get_passage_by_id
from leann.api import LeannBuilder
import tempfile
import shutil


def test_get_passage_by_id(tmp_path):
    """Test retrieving a passage by ID from an index."""
    # Create an index
    index_dir = tmp_path / "test_index"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index.leann")
    
    # Build index with known passage IDs
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("First passage content.", metadata={"id": "passage_1", "title": "First"})
    builder.add_text("Second passage content.", metadata={"id": "passage_2", "title": "Second"})
    builder.build_index(index_path)
    
    # Retrieve a passage by ID
    passage_data = get_passage_by_id(index_path, "passage_1")
    
    # Verify passage data
    assert isinstance(passage_data, dict), "Should return a dictionary"
    assert "id" in passage_data or "text" in passage_data, "Should contain passage data"
    assert passage_data.get("text") == "First passage content." or "First" in str(passage_data), "Should retrieve correct passage"
    
    # Clean up
    shutil.rmtree(index_dir)


def test_get_passage_by_id_not_found(tmp_path):
    """Test retrieving a non-existent passage ID should raise KeyError."""
    # Create an index
    index_dir = tmp_path / "test_index2"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Some content.", metadata={"id": "passage_1"})
    builder.build_index(index_path)
    
    # Try to get non-existent passage
    with pytest.raises(KeyError):
        get_passage_by_id(index_path, "nonexistent_id")
    
    shutil.rmtree(index_dir)

