# new_test_case_file

import pytest
from pathlib import Path
from case15 import batch_get_passages
from leann.api import LeannBuilder
import shutil


def test_batch_get_passages(tmp_path):
    """Test batch retrieval of multiple passages."""
    index_dir = tmp_path / "test_index"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index.leann")
    
    # Build index with known passage IDs
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("First passage content.", metadata={"id": "passage_1", "title": "First"})
    builder.add_text("Second passage content.", metadata={"id": "passage_2", "title": "Second"})
    builder.add_text("Third passage content.", metadata={"id": "passage_3", "title": "Third"})
    builder.build_index(index_path)
    
    # Batch retrieve passages
    passage_ids = ["passage_1", "passage_2", "passage_999"]  # One non-existent
    results = batch_get_passages(index_path, passage_ids)
    
    # Verify results
    assert len(results) == 3, "Should return results for all requested IDs"
    assert results["passage_1"] is not None, "Should find passage_1"
    assert results["passage_2"] is not None, "Should find passage_2"
    assert results["passage_999"] is None, "Should return None for non-existent passage"
    
    # Verify passage data structure
    assert "text" in results["passage_1"] or "id" in results["passage_1"], "Passage data should contain text or id"
    
    shutil.rmtree(index_dir)


def test_batch_get_passages_empty_list(tmp_path):
    """Test batch retrieval with empty list."""
    index_dir = tmp_path / "test_index2"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Test content.", metadata={"id": "passage_1"})
    builder.build_index(index_path)
    
    results = batch_get_passages(index_path, [])
    
    assert results == {}, "Should return empty dict for empty list"
    
    shutil.rmtree(index_dir)


def test_batch_get_passages_nonexistent_index():
    """Test batch retrieval with non-existent index should raise FileNotFoundError."""
    with pytest.raises(FileNotFoundError):
        batch_get_passages("/nonexistent/path.leann", ["passage_1"])
