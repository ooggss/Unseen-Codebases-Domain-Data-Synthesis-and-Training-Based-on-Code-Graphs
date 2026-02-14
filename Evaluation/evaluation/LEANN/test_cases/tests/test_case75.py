# new_test_case_file

import pytest
from pathlib import Path
from case75 import build_index_with_validation_and_search
import shutil


def test_build_index_with_validation_and_search(tmp_path):
    """Test building index with validation and search."""
    index_path = str(tmp_path / "test_index.leann")
    
    documents = [
        {"text": "Python programming language", "metadata": {"category": "tech"}},
        {"text": "Machine learning algorithms", "metadata": {"category": "science"}}
    ]
    
    result = build_index_with_validation_and_search(
        documents, index_path, validation_query="Python", expected_min_results=1
    )
    
    assert result["build_success"], "Build should succeed"
    assert result["validation_success"], "Validation should pass"
    assert result["validation_results_count"] >= 1, "Should have validation results"
    assert result["index_path"] == index_path, "Should return correct path"


def test_build_index_with_validation_and_search_empty():
    """Test with empty documents should raise ValueError."""
    with pytest.raises(ValueError, match="documents list cannot be empty"):
        build_index_with_validation_and_search([], "/tmp/test.leann", "query")
