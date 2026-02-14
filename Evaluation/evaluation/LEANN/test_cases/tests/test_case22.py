# new_test_case_file

import pytest
from pathlib import Path
from case22 import build_index_from_json_documents
import json
import shutil


def test_build_index_from_json_documents(tmp_path):
    """Test building index from JSON file."""
    json_file = tmp_path / "documents.json"
    index_path = str(tmp_path / "test_index.leann")
    
    # Create JSON file
    documents = [
        {"text": "Python is a programming language", "category": "tech", "rating": 5},
        {"text": "JavaScript is used for web development", "category": "tech", "rating": 4},
        {"text": "Machine learning uses algorithms", "category": "science", "rating": 5}
    ]
    with open(json_file, "w", encoding="utf-8") as f:
        json.dump(documents, f)
    
    result_path = build_index_from_json_documents(str(json_file), index_path)
    
    assert result_path == index_path, "Should return the index path"
    # Check if index was created (metadata file should exist)
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_from_json_documents_with_metadata_fields(tmp_path):
    """Test building index with specific metadata fields."""
    json_file = tmp_path / "documents2.json"
    index_path = str(tmp_path / "test_index2.leann")
    
    documents = [
        {"text": "Test content", "category": "tech", "rating": 5, "author": "John", "year": 2024}
    ]
    with open(json_file, "w", encoding="utf-8") as f:
        json.dump(documents, f)
    
    build_index_from_json_documents(str(json_file), index_path, metadata_fields=["category", "rating"])
    
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_from_json_documents_missing_text_field(tmp_path):
    """Test building index with missing text field should raise ValueError."""
    json_file = tmp_path / "documents3.json"
    index_path = str(tmp_path / "test_index3.leann")
    
    documents = [{"category": "tech"}]  # Missing text field
    with open(json_file, "w", encoding="utf-8") as f:
        json.dump(documents, f)
    
    with pytest.raises(ValueError, match="missing required field"):
        build_index_from_json_documents(str(json_file), index_path)


def test_build_index_from_json_documents_nonexistent_file():
    """Test building index with non-existent JSON file should raise FileNotFoundError."""
    with pytest.raises(FileNotFoundError):
        build_index_from_json_documents("/nonexistent/file.json", "/tmp/test.leann")
