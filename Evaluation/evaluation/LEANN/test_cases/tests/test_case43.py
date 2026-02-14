# new_test_case_file

import pytest
from pathlib import Path
from case43 import search_multiple_indexes, merge_search_results
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_multiple_indexes_and_merge(tmp_path):
    """Test searching multiple indexes and merging results."""
    # Build two indexes
    index1_path = str(tmp_path / "index1.leann")
    index2_path = str(tmp_path / "index2.leann")
    
    builder1 = LeannBuilder(backend_name="hnsw")
    builder1.add_text("Python programming language", metadata={"source": "index1"})
    builder1.build_index(index1_path)
    
    builder2 = LeannBuilder(backend_name="hnsw")
    builder2.add_text("Python web frameworks", metadata={"source": "index2"})
    builder2.build_index(index2_path)
    
    # Search multiple indexes
    index_paths = [index1_path, index2_path]
    results_by_index = search_multiple_indexes(index_paths, "Python", top_k_per_index=2)
    
    assert len(results_by_index) == 2, "Should have results from both indexes"
    assert all(isinstance(results, list) for results in results_by_index.values()), \
        "All values should be lists"
    
    # Merge results
    merged = merge_search_results(results_by_index, global_top_k=5, deduplicate=True)
    
    assert len(merged) > 0, "Should have merged results"
    assert all(isinstance(r, SearchResult) for r in merged), "All results should be SearchResult objects"
    assert all("source_index" in (r.metadata or {}) for r in merged), \
        "All results should have source_index metadata"
    
    # Check deduplication
    texts = [r.text for r in merged]
    assert len(texts) == len(set(texts)), "Results should be deduplicated"


def test_search_multiple_indexes_empty():
    """Test with empty index_paths should raise ValueError."""
    with pytest.raises(ValueError, match="index_paths cannot be empty"):
        search_multiple_indexes([], "query")
