# new_test_case_file

import pytest
from pathlib import Path
from case72 import search_with_result_merging
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_result_merging(tmp_path):
    """Test search with multiple queries and result merging."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming language")
    builder.add_text("Machine learning algorithms")
    builder.add_text("Web development frameworks")
    builder.build_index(index_path)
    
    queries = ["Python", "machine", "web"]
    results = search_with_result_merging(index_path, queries, top_k_per_query=2, global_top_k=5)
    
    assert len(results) > 0, "Should return merged results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    
    # Check deduplication
    texts = [r.text for r in results]
    assert len(texts) == len(set(texts)), "Results should be deduplicated"


def test_search_with_result_merging_empty():
    """Test with empty queries should raise ValueError."""
    with pytest.raises(ValueError, match="queries list cannot be empty"):
        search_with_result_merging("/tmp/test.leann", [])
