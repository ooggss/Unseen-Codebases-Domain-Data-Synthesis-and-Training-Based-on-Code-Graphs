# new_test_case_file

import pytest
from pathlib import Path
from case68 import search_with_score_normalization
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_score_normalization(tmp_path):
    """Test search with score normalization."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming language")
    builder.add_text("Machine learning algorithms")
    builder.build_index(index_path)
    
    results = search_with_score_normalization(index_path, "Python", normalize_to_range=(0.0, 1.0), top_k=5)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert all(0.0 <= r.score <= 1.0 for r in results), "All scores should be in normalized range"


def test_search_with_score_normalization_invalid_range():
    """Test with invalid range should raise ValueError."""
    with pytest.raises(ValueError, match="min must be less than max"):
        search_with_score_normalization("/tmp/test.leann", "query", normalize_to_range=(1.0, 0.0))
