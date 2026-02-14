# new_test_case_file

import pytest
from pathlib import Path
from case63 import get_passages_by_text_contains
from leann.api import LeannBuilder
import shutil


def test_get_passages_by_text_contains(tmp_path):
    """Test retrieving passages by text contains."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming language")
    builder.add_text("JavaScript web development")
    builder.add_text("Machine learning algorithms")
    builder.build_index(index_path)
    
    passages = get_passages_by_text_contains(index_path, "Python", case_sensitive=False)
    
    assert len(passages) >= 1, "Should find passages containing text"
    assert all("Python" in p.get("text", "").lower() or "python" in p.get("text", "").lower() 
               for p in passages), "All passages should contain search text"


def test_get_passages_by_text_contains_empty():
    """Test with empty search_text should raise ValueError."""
    with pytest.raises(ValueError, match="search_text cannot be empty"):
        get_passages_by_text_contains("/tmp/test.leann", "")
