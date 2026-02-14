# new_test_case_file

import pytest
from pathlib import Path
from case58 import get_passages_by_text_length
from leann.api import LeannBuilder
import shutil


def test_get_passages_by_text_length(tmp_path):
    """Test retrieving passages by text length."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Short")
    builder.add_text("This is a longer passage with more content")
    builder.add_text("Medium length text here")
    builder.build_index(index_path)
    
    passages = get_passages_by_text_length(index_path, min_length=10, max_length=30)
    
    assert len(passages) > 0, "Should find passages in length range"
    assert all(10 <= len(p.get("text", "")) <= 30 for p in passages), \
        "All passages should be in length range"


def test_get_passages_by_text_length_invalid():
    """Test with invalid length range should raise ValueError."""
    with pytest.raises(ValueError, match="max_length must be >= min_length"):
        get_passages_by_text_length("/tmp/test.leann", min_length=20, max_length=10)
