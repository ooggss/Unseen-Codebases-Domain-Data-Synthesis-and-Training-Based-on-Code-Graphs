# new_test_case_file

import pytest
from pathlib import Path
from case55 import search_with_custom_scoring
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_custom_scoring(tmp_path):
    """Test search with custom score multiplier."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming language")
    builder.add_text("Machine learning algorithms")
    builder.build_index(index_path)
    
    results = search_with_custom_scoring(index_path, "Python", score_multiplier=1.5, top_k=5)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert all(r.score >= 0 for r in results), "All scores should be non-negative"


def test_search_with_custom_scoring_negative():
    """Test with negative multiplier should raise ValueError."""
    with pytest.raises(ValueError, match="score_multiplier must be non-negative"):
        search_with_custom_scoring("/tmp/test.leann", "query", score_multiplier=-1.0)
