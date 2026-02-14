# new_test_case_file

import pytest
from pathlib import Path
from case67 import build_index_with_auto_metadata
import shutil


def test_build_index_with_auto_metadata(tmp_path):
    """Test building index with auto-generated metadata."""
    index_path = str(tmp_path / "test_index.leann")
    
    texts = ["Python tutorial", "JavaScript guide", "Machine learning"]
    
    def metadata_func(text, index):
        return {"index": index, "length": len(text), "has_python": "python" in text.lower()}
    
    result_path = build_index_with_auto_metadata(texts, index_path, auto_metadata_func=metadata_func)
    
    assert result_path == index_path, "Should return the index path"
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_with_auto_metadata_no_func(tmp_path):
    """Test building index without metadata function."""
    index_path = str(tmp_path / "test_index2.leann")
    
    texts = ["Test content"]
    
    build_index_with_auto_metadata(texts, index_path, auto_metadata_func=None)
    
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_with_auto_metadata_empty():
    """Test with empty texts should raise ValueError."""
    with pytest.raises(ValueError, match="texts list cannot be empty"):
        build_index_with_auto_metadata([], "/tmp/test.leann")
