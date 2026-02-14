# new_test_case_file

import pytest
from pathlib import Path
from case3 import search_in_index
from leann.api import LeannBuilder, SearchResult
import tempfile
import shutil


def test_search_in_index(tmp_path):
    """Test searching in a LEANN index."""
    # First, create an index with some documents
    index_dir = tmp_path / "test_index"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index.leann")
    
    # Build a small index
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python is a programming language.", metadata={"topic": "programming", "language": "Python"})
    builder.add_text("Machine learning uses algorithms to learn from data.", metadata={"topic": "ML", "category": "AI"})
    builder.add_text("Vector databases store high-dimensional vectors.", metadata={"topic": "databases", "type": "vector"})
    builder.build_index(index_path)
    
    # Search in the index
    results = search_in_index(index_path, "programming language", top_k=2)
    
    # Verify results
    assert len(results) > 0, "Should return at least one result"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    assert len(results) <= 2, "Should return at most top_k results"
    
    # Verify first result contains relevant content
    assert "Python" in results[0].text or "programming" in results[0].text.lower(), "First result should be relevant"
    
    # Clean up
    shutil.rmtree(index_dir)


def test_search_in_index_empty_query(tmp_path):
    """Test searching with empty query."""
    index_dir = tmp_path / "test_index2"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Some text content here.")
    builder.build_index(index_path)
    
    # Empty query should still return results (may be empty or all)
    results = search_in_index(index_path, "", top_k=5)
    
    # Should return a list (may be empty)
    assert isinstance(results, list), "Should return a list"
    
    shutil.rmtree(index_dir)

