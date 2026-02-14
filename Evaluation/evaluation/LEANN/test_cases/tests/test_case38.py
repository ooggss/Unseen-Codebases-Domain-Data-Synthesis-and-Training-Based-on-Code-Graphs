# new_test_case_file

import pytest
from pathlib import Path
from case38 import build_index_with_metadata_validation
import shutil


def test_build_index_with_metadata_validation(tmp_path):
    """Test building index with metadata validation."""
    index_path = str(tmp_path / "test_index.leann")
    
    documents = [
        {"text": "Python tutorial", "metadata": {"category": "tech", "rating": 5}},
        {"text": "JavaScript guide", "metadata": {"category": "web", "rating": 4}}
    ]
    
    result_path = build_index_with_metadata_validation(documents, index_path, required_metadata_fields=["category", "rating"])
    
    assert result_path == index_path, "Should return the index path"
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_with_metadata_validation_missing_field(tmp_path):
    """Test with missing required field should raise ValueError."""
    index_path = str(tmp_path / "test_index2.leann")
    
    documents = [
        {"text": "Python tutorial", "metadata": {"category": "tech"}}  # Missing rating
    ]
    
    with pytest.raises(ValueError, match="missing required metadata fields"):
        build_index_with_metadata_validation(documents, index_path, required_metadata_fields=["category", "rating"])


def test_build_index_with_metadata_validation_no_required_fields(tmp_path):
    """Test building without required fields."""
    index_path = str(tmp_path / "test_index3.leann")
    
    documents = [
        {"text": "Python tutorial", "metadata": {"category": "tech"}}
    ]
    
    build_index_with_metadata_validation(documents, index_path, required_metadata_fields=None)
    
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"
