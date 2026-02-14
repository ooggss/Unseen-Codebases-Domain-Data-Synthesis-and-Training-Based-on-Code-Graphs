# new_test_case_file

import pytest
from pathlib import Path
from case26 import search_and_group_by_metadata
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_and_group_by_metadata(tmp_path):
    """Test search and grouping by metadata field."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "language": "python"})
    builder.add_text("JavaScript guide", metadata={"category": "tech", "language": "javascript"})
    builder.add_text("Python advanced", metadata={"category": "tech", "language": "python"})
    builder.add_text("Web design", metadata={"category": "web", "language": "html"})
    builder.build_index(index_path)
    
    grouped = search_and_group_by_metadata(index_path, "programming", "category", top_k=10)
    
    assert isinstance(grouped, dict), "Should return a dictionary"
    assert len(grouped) > 0, "Should have at least one group"
    assert all(isinstance(v, list) for v in grouped.values()), "All values should be lists"
    assert all(isinstance(r, SearchResult) for group in grouped.values() for r in group), \
        "All items in groups should be SearchResult objects"


def test_search_and_group_by_metadata_unknown_field(tmp_path):
    """Test grouping when some results don't have the grouping field."""
    index_path = str(tmp_path / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Content with category", metadata={"category": "tech"})
    builder.add_text("Content without category", metadata={})
    builder.build_index(index_path)
    
    grouped = search_and_group_by_metadata(index_path, "Content", "category", top_k=10)
    
    assert "unknown" in grouped or "tech" in grouped, "Should handle missing field as 'unknown' or have 'tech' group"
