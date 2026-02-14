# new_test_case_file

import pytest
from pathlib import Path
from case28 import search_with_score_threshold
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_score_threshold(tmp_path):
    """Test search with score threshold filtering."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming language")
    builder.add_text("Machine learning algorithms")
    builder.add_text("Web development frameworks")
    builder.build_index(index_path)
    
    # Search with threshold
    results = search_with_score_threshold(index_path, "Python", min_score=0.0, top_k=10)
    
    assert len(results) > 0, "Should return results above threshold"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert all(r.score >= 0.0 for r in results), "All results should meet threshold"


def test_search_with_score_threshold_high_threshold(tmp_path):
    """Test search with high score threshold."""
    index_path = str(tmp_path / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming")
    builder.add_text("JavaScript development")
    builder.build_index(index_path)
    
    # High threshold might filter out all results
    results = search_with_score_threshold(index_path, "Python", min_score=0.9, top_k=10)
    
    assert isinstance(results, list), "Should return a list"
    assert all(r.score >= 0.9 for r in results), "All results should meet high threshold"


def test_search_with_score_threshold_invalid_range():
    """Test with invalid score range should raise ValueError."""
    with pytest.raises(ValueError, match="min_score must be in range"):
        search_with_score_threshold("/tmp/test.leann", "query", min_score=1.5, top_k=10)
