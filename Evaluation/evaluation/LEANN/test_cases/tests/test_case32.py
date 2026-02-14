# new_test_case_file

import pytest
from pathlib import Path
from case32 import search_with_complexity_adjustment
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_complexity_adjustment(tmp_path):
    """Test search with complexity adjustment."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming language")
    builder.add_text("Machine learning algorithms")
    builder.build_index(index_path)
    
    results = search_with_complexity_adjustment(index_path, "Python", initial_complexity=64, max_results=5)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert all(r.score >= 0.0 for r in results), "All results should meet minimum score"


def test_search_with_complexity_adjustment_invalid_complexity():
    """Test with invalid complexity should raise ValueError."""
    with pytest.raises(ValueError, match="complexity must be in range"):
        search_with_complexity_adjustment("/tmp/test.leann", "query", initial_complexity=200)
