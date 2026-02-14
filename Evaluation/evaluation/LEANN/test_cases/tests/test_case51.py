# new_test_case_file

import pytest
from pathlib import Path
from case51 import search_with_field_exclusion
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_field_exclusion(tmp_path):
    """Test search with field exclusion."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "status": "active"})
    builder.add_text("JavaScript guide", metadata={"category": "tech", "status": "deprecated"})
    builder.add_text("Web design", metadata={"category": "web", "status": "active"})
    builder.build_index(index_path)
    
    results = search_with_field_exclusion(index_path, "programming", "status", ["deprecated"], top_k=10)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert all(r.metadata.get("status") != "deprecated" for r in results if r.metadata), \
        "Should exclude deprecated items"


def test_search_with_field_exclusion_empty_values():
    """Test with empty exclude_values should raise ValueError."""
    with pytest.raises(ValueError, match="exclude_values cannot be empty"):
        search_with_field_exclusion("/tmp/test.leann", "query", "field", [])
