# new_test_case_file

import pytest
from pathlib import Path
from case65 import build_index_and_search
from leann.api import SearchResult
import shutil


def test_build_index_and_search(tmp_path):
    """Test building index and searching."""
    index_path = str(tmp_path / "test_index.leann")
    
    documents = [
        {"text": "Python programming language", "metadata": {"category": "tech"}},
        {"text": "Machine learning algorithms", "metadata": {"category": "science"}}
    ]
    
    results = build_index_and_search(documents, index_path, "Python", top_k=5)
    
    assert isinstance(results, list), "Should return a list"
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"


def test_build_index_and_search_empty_documents():
    """Test with empty documents should raise ValueError."""
    with pytest.raises(ValueError, match="documents list cannot be empty"):
        build_index_and_search([], "/tmp/test.leann", "query")


def test_build_index_and_search_empty_query(tmp_path):
    """Test with empty query should raise ValueError."""
    documents = [{"text": "Test content"}]
    with pytest.raises(ValueError, match="query cannot be empty"):
        build_index_and_search(documents, "/tmp/test.leann", "")
