# new_test_case_file

import pytest
from pathlib import Path
from case30 import search_and_count_by_field
from leann.api import LeannBuilder
import shutil


def test_search_and_count_by_field(tmp_path):
    """Test search and counting by metadata field."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "language": "python"})
    builder.add_text("JavaScript guide", metadata={"category": "tech", "language": "javascript"})
    builder.add_text("Python advanced", metadata={"category": "tech", "language": "python"})
    builder.add_text("Web design", metadata={"category": "web", "language": "html"})
    builder.build_index(index_path)
    
    counts = search_and_count_by_field(index_path, "programming", "category", top_k=10)
    
    assert isinstance(counts, dict), "Should return a dictionary"
    assert len(counts) > 0, "Should have at least one count"
    assert all(isinstance(v, int) for v in counts.values()), "All values should be integers"
    assert all(v > 0 for v in counts.values()), "All counts should be positive"


def test_search_and_count_by_field_unknown_values(tmp_path):
    """Test counting when some results don't have the field."""
    index_path = str(tmp_path / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Content with category", metadata={"category": "tech"})
    builder.add_text("Content without category", metadata={})
    builder.build_index(index_path)
    
    counts = search_and_count_by_field(index_path, "Content", "category", top_k=10)
    
    assert "unknown" in counts or "tech" in counts, "Should handle missing field as 'unknown' or count 'tech'"
