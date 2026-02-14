
import pytest
from pathlib import Path
from case18 import update_passage_metadata_in_memory
from leann.api import LeannBuilder
import shutil


def test_update_passage_metadata_in_memory(tmp_path):
    """Test updating passage metadata in memory."""
    index_dir = tmp_path / "test_index3"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index3.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Original content.", metadata={"id": "passage_1", "category": "tech", "rating": 4.0})
    builder.build_index(index_path)
    
    # Update metadata
    metadata_updates = {"rating": 5.0, "reviewed": True}
    updated = update_passage_metadata_in_memory(index_path, "passage_1", metadata_updates)
    
    # Verify update
    assert "metadata" in updated, "Should have metadata field"
    assert updated["metadata"]["rating"] == 5.0, "Rating should be updated"
    assert updated["metadata"]["reviewed"] is True, "New field should be added"
    assert updated["metadata"]["category"] == "tech", "Existing field should be preserved"
    
    shutil.rmtree(index_dir)


def test_update_passage_metadata_nonexistent(tmp_path):
    """Test updating metadata for non-existent passage should raise KeyError."""
    index_dir = tmp_path / "test_index4"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index4.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Content.", metadata={"id": "passage_1"})
    builder.build_index(index_path)
    
    with pytest.raises(KeyError):
        update_passage_metadata_in_memory(index_path, "nonexistent_id", {"key": "value"})
    
    shutil.rmtree(index_dir)
