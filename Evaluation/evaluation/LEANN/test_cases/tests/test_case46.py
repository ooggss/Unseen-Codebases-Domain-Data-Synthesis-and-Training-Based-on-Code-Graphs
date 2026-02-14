# new_test_case_file

import pytest
from pathlib import Path
from case46 import search_with_timeout
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_timeout(tmp_path):
    """Test search with timeout."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming language")
    builder.add_text("Machine learning algorithms")
    builder.build_index(index_path)
    
    results = search_with_timeout(index_path, "Python", top_k=5, timeout_seconds=10.0)
    
    assert isinstance(results, list), "Should return a list"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"


def test_search_with_timeout_invalid():
    """Test with invalid timeout should raise ValueError."""
    with pytest.raises(ValueError, match="timeout_seconds must be greater than 0"):
        search_with_timeout("/tmp/test.leann", "query", timeout_seconds=0)
