# new_test_case_file

import pytest
from pathlib import Path
from case57 import search_and_extract_field_values
from leann.api import LeannBuilder
import shutil


def test_search_and_extract_field_values(tmp_path):
    """Test search and field value extraction."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "language": "python"})
    builder.add_text("JavaScript guide", metadata={"category": "tech", "language": "javascript"})
    builder.add_text("Python advanced", metadata={"category": "tech", "language": "python"})
    builder.build_index(index_path)
    
    values = search_and_extract_field_values(index_path, "programming", "language", top_k=10)
    
    assert isinstance(values, list), "Should return a list"
    assert len(values) > 0, "Should extract values"
    assert "python" in values, "Should include python"
    assert values.count("python") == 1, "Should be unique values"
