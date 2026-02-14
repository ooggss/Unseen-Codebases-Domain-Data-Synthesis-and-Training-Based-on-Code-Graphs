# new_test_case_file

import pytest
from pathlib import Path
from case66 import search_with_field_requirement
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_field_requirement(tmp_path):
    """Test search with field requirement."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "rating": 5})
    builder.add_text("JavaScript guide", metadata={"category": "web"})
    builder.add_text("Machine learning", metadata={})
    builder.build_index(index_path)
    
    results = search_with_field_requirement(index_path, "programming", "rating", top_k=10)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert all("rating" in (r.metadata or {}) for r in results), "All results should have rating field"
