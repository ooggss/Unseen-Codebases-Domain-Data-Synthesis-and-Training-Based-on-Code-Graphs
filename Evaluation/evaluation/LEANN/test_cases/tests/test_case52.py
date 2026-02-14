# new_test_case_file

import pytest
from pathlib import Path
from case52 import build_index_from_text_file
import shutil


def test_build_index_from_text_file(tmp_path):
    """Test building index from text file."""
    text_file = tmp_path / "content.txt"
    text_file.write_text("Python is a programming language. Machine learning uses algorithms.")
    
    index_path = str(tmp_path / "test_index.leann")
    result_path = build_index_from_text_file(str(text_file), index_path)
    
    assert result_path == index_path, "Should return the index path"
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_from_text_file_with_metadata(tmp_path):
    """Test building index with metadata."""
    text_file = tmp_path / "content2.txt"
    text_file.write_text("Test content")
    
    index_path = str(tmp_path / "test_index2.leann")
    build_index_from_text_file(str(text_file), index_path, metadata={"source": "file", "author": "test"})
    
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_from_text_file_nonexistent():
    """Test with non-existent file should raise FileNotFoundError."""
    with pytest.raises(FileNotFoundError):
        build_index_from_text_file("/nonexistent/file.txt", "/tmp/test.leann")


def test_build_index_from_text_file_empty(tmp_path):
    """Test with empty file should raise ValueError."""
    text_file = tmp_path / "empty.txt"
    text_file.write_text("")
    
    with pytest.raises(ValueError, match="Text file is empty"):
        build_index_from_text_file(str(text_file), "/tmp/test.leann")
