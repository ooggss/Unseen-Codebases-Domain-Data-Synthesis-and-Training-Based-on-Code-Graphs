# new_test_case_file

import pytest
from pathlib import Path
from case59 import search_with_result_expansion
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_result_expansion(tmp_path):
    """Test search with result expansion."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial 1", metadata={"category": "tech"})
    builder.add_text("Python tutorial 2", metadata={"category": "tech"})
    builder.add_text("JavaScript guide", metadata={"category": "web"})
    builder.build_index(index_path)
    
    results = search_with_result_expansion(index_path, "programming", "category", expansion_count=1, top_k=2)
    
    assert len(results) >= 2, "Should have at least initial results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"


def test_search_with_result_expansion_negative():
    """Test with negative expansion_count should raise ValueError."""
    with pytest.raises(ValueError, match="expansion_count must be non-negative"):
        search_with_result_expansion("/tmp/test.leann", "query", "field", expansion_count=-1)
