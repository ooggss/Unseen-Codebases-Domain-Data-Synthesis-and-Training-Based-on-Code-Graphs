# new_test_case_file

import pytest
from pathlib import Path
from case35 import find_passages_by_text_pattern
from leann.api import LeannBuilder
import shutil


def test_find_passages_by_text_pattern(tmp_path):
    """Test finding passages by text pattern."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python is a programming language")
    builder.add_text("JavaScript is used for web development")
    builder.add_text("Machine learning algorithms")
    builder.build_index(index_path)
    
    passages = find_passages_by_text_pattern(index_path, "Python", case_sensitive=False)
    
    assert len(passages) >= 1, "Should find at least one passage"
    assert all("Python" in p.get("text", "").lower() or "python" in p.get("text", "").lower() 
               for p in passages), "All passages should contain pattern"


def test_find_passages_by_text_pattern_case_sensitive(tmp_path):
    """Test case-sensitive pattern matching."""
    index_path = str(tmp_path / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python programming")
    builder.add_text("python tutorial")
    builder.build_index(index_path)
    
    passages = find_passages_by_text_pattern(index_path, "Python", case_sensitive=True)
    
    # Should only match "Python" (capitalized)
    assert len(passages) >= 1, "Should find passages with exact case match"


def test_find_passages_by_text_pattern_empty():
    """Test with empty pattern should raise ValueError."""
    with pytest.raises(ValueError, match="pattern cannot be empty"):
        find_passages_by_text_pattern("/tmp/test.leann", "")
