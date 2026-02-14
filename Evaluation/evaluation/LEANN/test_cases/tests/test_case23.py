# new_test_case_file

import pytest
from pathlib import Path
from case23 import search_and_rank_by_metadata_field
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_and_rank_by_metadata_field(tmp_path):
    """Test search and ranking by metadata field."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"priority": 3, "category": "tech"})
    builder.add_text("Python advanced guide", metadata={"priority": 5, "category": "tech"})
    builder.add_text("Python basics", metadata={"priority": 1, "category": "tech"})
    builder.add_text("JavaScript tutorial", metadata={"priority": 4, "category": "web"})
    builder.build_index(index_path)
    
    results = search_and_rank_by_metadata_field(index_path, "Python", "priority", top_k=3)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    
    # Check that results are sorted by priority (descending)
    priorities = [r.metadata.get("priority", 0) for r in results if "priority" in r.metadata]
    if len(priorities) > 1:
        assert priorities == sorted(priorities, reverse=True), "Results should be sorted by priority descending"


def test_search_and_rank_by_metadata_field_missing_field(tmp_path):
    """Test ranking when some results don't have the ranking field."""
    index_path = str(tmp_path / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Content with priority", metadata={"priority": 5})
    builder.add_text("Content without priority", metadata={"category": "tech"})
    builder.build_index(index_path)
    
    results = search_and_rank_by_metadata_field(index_path, "Content", "priority", top_k=5)
    
    assert len(results) > 0, "Should return results"
    # Results with priority should come first
    has_priority = [r for r in results if "priority" in (r.metadata or {})]
    assert len(has_priority) > 0, "Should include results with priority field"
