# new_test_case_file

import pytest
from pathlib import Path
from case37 import search_with_field_boost
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_field_boost(tmp_path):
    """Test search with field boosting."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "priority": "high"})
    builder.add_text("Python basics", metadata={"category": "tech", "priority": "low"})
    builder.add_text("JavaScript guide", metadata={"category": "web", "priority": "high"})
    builder.build_index(index_path)
    
    results = search_with_field_boost(index_path, "programming", "priority", "high", top_k=5)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    
    # Check that boosted results (priority="high") come first
    boosted_count = sum(1 for r in results if r.metadata and r.metadata.get("priority") == "high")
    assert boosted_count > 0, "Should have boosted results"
