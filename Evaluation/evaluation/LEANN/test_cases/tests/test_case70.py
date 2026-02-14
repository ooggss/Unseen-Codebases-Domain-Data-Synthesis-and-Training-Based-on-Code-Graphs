# new_test_case_file

import pytest
from pathlib import Path
from case70 import search_with_field_priority
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_field_priority(tmp_path):
    """Test search with field priority."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"priority": "high", "category": "tech"})
    builder.add_text("Python basics", metadata={"priority": "low", "category": "tech"})
    builder.add_text("JavaScript guide", metadata={"priority": "medium", "category": "web"})
    builder.build_index(index_path)
    
    results = search_with_field_priority(index_path, "programming", "priority", ["high", "medium", "low"], top_k=5)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    
    # High priority should come first
    priorities = [r.metadata.get("priority") for r in results if r.metadata and "priority" in r.metadata]
    if "high" in priorities and "low" in priorities:
        high_index = priorities.index("high")
        low_index = priorities.index("low")
        assert high_index < low_index, "High priority should come before low"


def test_search_with_field_priority_empty():
    """Test with empty priority_values should raise ValueError."""
    with pytest.raises(ValueError, match="priority_values cannot be empty"):
        search_with_field_priority("/tmp/test.leann", "query", "field", [])
