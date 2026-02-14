# new_test_case_file

import pytest
from pathlib import Path
from case74 import search_with_field_aggregation
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_field_aggregation(tmp_path):
    """Test search with field aggregation."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech"})
    builder.add_text("JavaScript guide", metadata={"category": "tech"})
    builder.add_text("Web design", metadata={"category": "web"})
    builder.build_index(index_path)
    
    grouped = search_with_field_aggregation(index_path, "programming", "category", top_k=10)
    
    assert isinstance(grouped, dict), "Should return a dictionary"
    assert len(grouped) > 0, "Should have at least one group"
    assert all(isinstance(v, list) for v in grouped.values()), "All values should be lists"
    assert all(isinstance(r, SearchResult) for group in grouped.values() for r in group), \
        "All items should be SearchResult objects"
