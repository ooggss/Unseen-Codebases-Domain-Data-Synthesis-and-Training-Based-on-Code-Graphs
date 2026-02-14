# new_test_case_file

import pytest
from pathlib import Path
from case62 import search_with_minimum_field_value
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_minimum_field_value(tmp_path):
    """Test search with minimum field value filter."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"rating": 5.0, "category": "tech"})
    builder.add_text("JavaScript guide", metadata={"rating": 3.0, "category": "tech"})
    builder.add_text("Web design", metadata={"rating": 4.5, "category": "web"})
    builder.build_index(index_path)
    
    results = search_with_minimum_field_value(index_path, "programming", "rating", min_value=4.0, top_k=10)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert all(float(r.metadata.get("rating", 0)) >= 4.0 for r in results if r.metadata and "rating" in r.metadata), \
        "All results should have rating >= 4.0"
