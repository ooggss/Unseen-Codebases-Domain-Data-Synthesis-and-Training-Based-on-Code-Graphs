# new_test_case_file

import pytest
from pathlib import Path
from case21 import search_with_metadata_filtering
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_metadata_filtering(tmp_path):
    """Test search with metadata filtering."""
    index_path = str(tmp_path / "test_index.leann")
    
    # Build index with metadata
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming language", metadata={"category": "tech", "rating": 5.0})
    builder.add_text("JavaScript web development", metadata={"category": "tech", "rating": 4.0})
    builder.add_text("Machine learning algorithms", metadata={"category": "science", "rating": 5.0})
    builder.add_text("Web design principles", metadata={"category": "web", "rating": 3.0})
    builder.build_index(index_path)
    
    # Search with filters
    filters = {"category": {"==": "tech"}, "rating": {">=": 4.0}}
    results = search_with_metadata_filtering(index_path, "programming", filters, top_k=5)
    
    assert len(results) > 0, "Should return filtered results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert all(r.metadata.get("category") == "tech" for r in results), "All results should be tech category"
    assert all(r.metadata.get("rating", 0) >= 4.0 for r in results), "All results should have rating >= 4.0"


def test_search_with_metadata_filtering_no_matches(tmp_path):
    """Test search with filters that match no results."""
    index_path = str(tmp_path / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Test content", metadata={"category": "tech"})
    builder.build_index(index_path)
    
    filters = {"category": {"==": "nonexistent"}}
    results = search_with_metadata_filtering(index_path, "test", filters, top_k=5)
    
    assert len(results) == 0, "Should return empty list when no matches"


def test_search_with_metadata_filtering_multiple_operators(tmp_path):
    """Test search with multiple filter operators."""
    index_path = str(tmp_path / "test_index3.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "tags": ["python", "programming"]})
    builder.add_text("JavaScript guide", metadata={"category": "tech", "tags": ["javascript"]})
    builder.build_index(index_path)
    
    filters = {"category": {"==": "tech"}, "tags": {"contains": "python"}}
    results = search_with_metadata_filtering(index_path, "tutorial", filters, top_k=5)
    
    assert len(results) > 0, "Should return results matching all filters"
    assert all("python" in str(r.metadata.get("tags", [])) for r in results), "All results should contain python tag"
