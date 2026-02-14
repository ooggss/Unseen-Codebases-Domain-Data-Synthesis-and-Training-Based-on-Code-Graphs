# new_test_case_file

import pytest
from pathlib import Path
from case54 import get_passage_statistics
from leann.api import LeannBuilder
import shutil


def test_get_passage_statistics(tmp_path):
    """Test getting passage statistics."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech"})
    builder.add_text("JavaScript guide", metadata={"category": "web"})
    builder.add_text("Machine learning")
    builder.build_index(index_path)
    
    stats = get_passage_statistics(index_path)
    
    assert stats["total_passages"] > 0, "Should have passages"
    assert stats["passages_with_metadata"] >= 2, "Should have passages with metadata"
    assert stats["passages_without_metadata"] >= 1, "Should have passages without metadata"
    assert stats["average_text_length"] > 0, "Should have average text length"
    assert isinstance(stats["average_text_length"], float), "Average should be float"
