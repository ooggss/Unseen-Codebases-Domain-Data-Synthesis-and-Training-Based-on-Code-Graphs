# new_test_case_file

import pytest
from pathlib import Path
from case27 import build_index_with_custom_chunking
import shutil


def test_build_index_with_custom_chunking(tmp_path):
    """Test building index with custom chunking parameters."""
    index_path = str(tmp_path / "test_index.leann")
    
    documents = [
        {"text": "Python is a programming language. It is widely used for web development and data science.", "metadata": {"category": "tech"}},
        {"text": "Machine learning is a subset of artificial intelligence.", "metadata": {"category": "science"}}
    ]
    
    result_path = build_index_with_custom_chunking(documents, index_path, chunk_size=256, chunk_overlap=128)
    
    assert result_path == index_path, "Should return the index path"
    # Check if index was created
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_with_custom_chunking_empty_documents():
    """Test with empty documents list should raise ValueError."""
    with pytest.raises(ValueError, match="cannot be empty"):
        build_index_with_custom_chunking([], "/tmp/test.leann")


def test_build_index_with_custom_chunking_invalid_chunk_size():
    """Test with invalid chunk_size should raise ValueError."""
    documents = [{"text": "Test content"}]
    with pytest.raises(ValueError, match="chunk_size must be greater than 0"):
        build_index_with_custom_chunking(documents, "/tmp/test.leann", chunk_size=0)


def test_build_index_with_custom_chunking_invalid_overlap():
    """Test with overlap >= chunk_size should raise ValueError."""
    documents = [{"text": "Test content"}]
    with pytest.raises(ValueError, match="chunk_overlap must be less than chunk_size"):
        build_index_with_custom_chunking(documents, "/tmp/test.leann", chunk_size=100, chunk_overlap=100)
