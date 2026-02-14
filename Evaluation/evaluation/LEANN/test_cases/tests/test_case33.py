# new_test_case_file

import pytest
from pathlib import Path
from case33 import build_index_from_text_list
import shutil


def test_build_index_from_text_list(tmp_path):
    """Test building index from text list."""
    index_path = str(tmp_path / "test_index.leann")
    
    texts = [
        "Python is a programming language",
        "Machine learning uses algorithms",
        "Web development involves HTML, CSS, and JavaScript"
    ]
    
    result_path = build_index_from_text_list(texts, index_path)
    
    assert result_path == index_path, "Should return the index path"
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_from_text_list_with_metadata(tmp_path):
    """Test building index with metadata."""
    index_path = str(tmp_path / "test_index2.leann")
    
    texts = ["Python tutorial", "JavaScript guide"]
    metadata_list = [{"category": "tech"}, {"category": "web"}]
    
    build_index_from_text_list(texts, index_path, metadata_list=metadata_list)
    
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_from_text_list_empty():
    """Test with empty list should raise ValueError."""
    with pytest.raises(ValueError, match="texts list cannot be empty"):
        build_index_from_text_list([], "/tmp/test.leann")


def test_build_index_from_text_list_metadata_mismatch():
    """Test with mismatched metadata length should raise ValueError."""
    texts = ["Text 1", "Text 2"]
    metadata_list = [{"category": "tech"}]  # Only one metadata dict
    
    with pytest.raises(ValueError, match="metadata_list length must match"):
        build_index_from_text_list(texts, "/tmp/test.leann", metadata_list=metadata_list)
