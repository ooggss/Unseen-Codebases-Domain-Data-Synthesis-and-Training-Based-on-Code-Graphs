# new_test_case_file

import pytest
from pathlib import Path
from case49 import search_with_fuzzy_matching
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_fuzzy_matching(tmp_path):
    """Test search with fuzzy matching threshold."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming language")
    builder.add_text("Machine learning algorithms")
    builder.build_index(index_path)
    
    results = search_with_fuzzy_matching(index_path, "Python", top_k=5, similarity_threshold=0.0)
    
    assert len(results) > 0, "Should return results above threshold"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert all(r.score >= 0.0 for r in results), "All results should meet threshold"


def test_search_with_fuzzy_matching_high_threshold(tmp_path):
    """Test with high similarity threshold."""
    index_path = str(tmp_path / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial")
    builder.build_index(index_path)
    
    results = search_with_fuzzy_matching(index_path, "Python", similarity_threshold=0.9, top_k=5)
    
    assert isinstance(results, list), "Should return a list"
    assert all(r.score >= 0.9 for r in results), "All results should meet high threshold"


def test_search_with_fuzzy_matching_invalid_threshold():
    """Test with invalid threshold should raise ValueError."""
    with pytest.raises(ValueError, match="similarity_threshold must be in range"):
        search_with_fuzzy_matching("/tmp/test.leann", "query", similarity_threshold=1.5)
