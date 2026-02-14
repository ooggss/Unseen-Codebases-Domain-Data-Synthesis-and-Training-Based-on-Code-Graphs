# new_test_case_file

import pytest
from pathlib import Path
from case71 import create_index_from_dict
import shutil


def test_create_index_from_dict(tmp_path):
    """Test creating index from dictionary."""
    index_path = str(tmp_path / "test_index.leann")
    
    data_dict = {
        "doc1": "Python programming language",
        "doc2": "Machine learning algorithms",
        "doc3": "Web development frameworks"
    }
    
    result_path = create_index_from_dict(data_dict, index_path)
    
    assert result_path == index_path, "Should return the index path"
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_create_index_from_dict_empty():
    """Test with empty dictionary should raise ValueError."""
    with pytest.raises(ValueError, match="data_dict cannot be empty"):
        create_index_from_dict({}, "/tmp/test.leann")
