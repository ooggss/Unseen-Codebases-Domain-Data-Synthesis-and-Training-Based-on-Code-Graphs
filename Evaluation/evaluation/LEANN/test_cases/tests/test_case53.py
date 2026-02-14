# new_test_case_file

import pytest
from pathlib import Path
from case53 import search_with_result_limit_per_field
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_result_limit_per_field(tmp_path):
    """Test search with result limit per field value."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial 1", metadata={"category": "tech"})
    builder.add_text("Python tutorial 2", metadata={"category": "tech"})
    builder.add_text("Python tutorial 3", metadata={"category": "tech"})
    builder.add_text("JavaScript guide", metadata={"category": "web"})
    builder.build_index(index_path)
    
    results = search_with_result_limit_per_field(index_path, "programming", "category", max_per_value=2, top_k=10)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    
    # Check that each category has at most 2 results
    category_counts = {}
    for result in results:
        category = result.metadata.get("category", "unknown") if result.metadata else "unknown"
        category_counts[category] = category_counts.get(category, 0) + 1
    
    assert all(count <= 2 for count in category_counts.values()), "Should have max 2 per category"


def test_search_with_result_limit_per_field_invalid():
    """Test with invalid max_per_value should raise ValueError."""
    with pytest.raises(ValueError, match="max_per_value must be greater than 0"):
        search_with_result_limit_per_field("/tmp/test.leann", "query", "field", max_per_value=0)
