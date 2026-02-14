# new_test_case_file

import pytest
from pathlib import Path
from case61 import build_and_verify_searchable
import shutil


def test_build_and_verify_searchable(tmp_path):
    """Test building index and verifying it is searchable."""
    index_path = str(tmp_path / "test_index.leann")
    
    documents = [
        {"text": "Python programming language", "metadata": {"category": "tech"}},
        {"text": "Machine learning algorithms", "metadata": {"category": "science"}}
    ]
    
    result = build_and_verify_searchable(documents, index_path, test_query="Python")
    
    assert result["index_path"] == index_path, "Should return correct path"
    assert result["is_searchable"], "Index should be searchable"
    assert result["test_results_count"] >= 0, "Should have test results count"


def test_build_and_verify_searchable_empty_documents():
    """Test with empty documents should raise ValueError."""
    with pytest.raises(ValueError, match="documents list cannot be empty"):
        build_and_verify_searchable([], "/tmp/test.leann")
