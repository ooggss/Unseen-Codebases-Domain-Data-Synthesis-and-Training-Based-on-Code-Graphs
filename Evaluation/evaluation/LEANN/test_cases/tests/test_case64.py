# new_test_case_file

import pytest
from pathlib import Path
from case64 import search_and_get_top_field_values
from leann.api import LeannBuilder
import shutil


def test_search_and_get_top_field_values(tmp_path):
    """Test search and getting top field values."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial 1", metadata={"category": "tech"})
    builder.add_text("Python tutorial 2", metadata={"category": "tech"})
    builder.add_text("JavaScript guide", metadata={"category": "web"})
    builder.build_index(index_path)
    
    top_values = search_and_get_top_field_values(index_path, "programming", "category", top_n=3)
    
    assert isinstance(top_values, list), "Should return a list"
    assert len(top_values) > 0, "Should have top values"
    assert all(isinstance(item, tuple) and len(item) == 2 for item in top_values), \
        "All items should be (value, count) tuples"
    assert all(count > 0 for _, count in top_values), "All counts should be positive"


def test_search_and_get_top_field_values_invalid():
    """Test with invalid top_n should raise ValueError."""
    with pytest.raises(ValueError, match="top_n must be greater than 0"):
        search_and_get_top_field_values("/tmp/test.leann", "query", "field", top_n=0)
