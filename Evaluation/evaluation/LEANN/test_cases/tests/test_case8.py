# new_test_case_file

import pytest
from pathlib import Path
from case8 import remove_index_by_name
from leann.api import LeannBuilder
import tempfile
import shutil


def test_remove_index_by_name_with_existing_index(tmp_path, monkeypatch):
    """Test removing an existing index."""
    original_dir = Path.cwd()
    
    try:
        monkeypatch.chdir(tmp_path)
        
        # Create index directory structure
        indexes_dir = tmp_path / ".leann" / "indexes" / "test_index"
        indexes_dir.mkdir(parents=True)
        
        # Build an index
        index_path = str(indexes_dir / "documents.leann")
        builder = LeannBuilder(backend_name="hnsw")
        builder.add_text("Test content.")
        builder.build_index(index_path)
        
        # Verify index exists before removal
        assert (indexes_dir / "documents.leann.meta.json").exists()
        
        # Remove the index with force=True to avoid interactive prompts
        result = remove_index_by_name("test_index", force=True)
        
        # Verify removal
        assert result is True, "Removal should succeed"
        assert not indexes_dir.exists(), "Index directory should be removed"
    finally:
        # Ensure we restore to original directory before cleanup
        if original_dir.exists():
            monkeypatch.chdir(original_dir)
        # Clean up
        if (tmp_path / ".leann").exists():
            shutil.rmtree(tmp_path / ".leann")


def test_remove_index_by_name_nonexistent(tmp_path, monkeypatch):
    """Test removing a non-existent index."""
    original_dir = Path.cwd()
    
    try:
        monkeypatch.chdir(tmp_path)
        
        # Try to remove non-existent index
        result = remove_index_by_name("nonexistent_index", force=True)
        
        # Should return False for non-existent index
        assert result is False, "Removal of non-existent index should return False"
    finally:
        if original_dir.exists():
            monkeypatch.chdir(original_dir)

