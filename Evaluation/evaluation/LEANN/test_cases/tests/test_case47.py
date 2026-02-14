# new_test_case_file

import pytest
from pathlib import Path
from case47 import search_with_field_weights
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_field_weights(tmp_path):
    """Test search with field-based score weighting."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"priority": "high", "rating": 5})
    builder.add_text("Python basics", metadata={"priority": "low", "rating": 3})
    builder.build_index(index_path)
    
    # Note: This test uses numeric weights, but the function applies them to scores
    # In a real scenario, you might want to use numeric metadata fields
    field_weights = {"rating": 1.2}
    
    results = search_with_field_weights(index_path, "Python", field_weights, top_k=5)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"


def test_search_with_field_weights_negative():
    """Test with negative weight should raise ValueError."""
    with pytest.raises(ValueError, match="All field weights must be non-negative"):
        search_with_field_weights("/tmp/test.leann", "query", {"field": -1.0}, top_k=5)
