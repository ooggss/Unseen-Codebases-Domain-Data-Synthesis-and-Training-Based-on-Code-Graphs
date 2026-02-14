# new_test_case_file

import pytest
from pathlib import Path
from case41 import build_and_validate_index, verify_index_integrity
from leann.api import LeannBuilder
import shutil


def test_build_and_validate_index(tmp_path):
    """Test building and validating an index."""
    index_path = str(tmp_path / "test_index.leann")
    
    documents = [
        {"text": "Python is a programming language", "metadata": {"category": "tech"}},
        {"text": "Machine learning uses algorithms", "metadata": {"category": "science"}}
    ]
    
    result = build_and_validate_index(documents, index_path)
    
    assert result["status"] == "success", "Build should succeed"
    assert result["document_count"] == 2, "Should index 2 documents"
    assert result["index_path"] == index_path, "Should return correct path"
    
    # Verify the index integrity
    verification = verify_index_integrity(index_path)
    
    assert verification["is_valid"], "Index should be valid"
    assert verification["passage_count"] > 0, "Should have passages"
    assert verification["metadata_file_exists"], "Metadata file should exist"
    assert len(verification["errors"]) == 0, "Should have no errors"


def test_build_and_validate_index_empty_documents():
    """Test with empty documents should raise ValueError."""
    with pytest.raises(ValueError, match="documents list cannot be empty"):
        build_and_validate_index([], "/tmp/test.leann")


def test_verify_index_integrity_nonexistent():
    """Test verifying non-existent index should raise FileNotFoundError."""
    with pytest.raises(FileNotFoundError):
        verify_index_integrity("/nonexistent/index.leann")
