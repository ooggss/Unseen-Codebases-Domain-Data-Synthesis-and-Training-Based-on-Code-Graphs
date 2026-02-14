# new_test_case_file

import pytest
from pathlib import Path
from case56 import build_index_with_metadata_template
import shutil


def test_build_index_with_metadata_template(tmp_path):
    """Test building index with metadata template."""
    index_path = str(tmp_path / "test_index.leann")
    
    documents = [
        {"text": "Python tutorial", "metadata": {"category": "tech"}},
        {"text": "JavaScript guide", "metadata": {"category": "web"}}
    ]
    
    template = {"source": "docs", "version": "1.0"}
    result_path = build_index_with_metadata_template(documents, index_path, metadata_template=template)
    
    assert result_path == index_path, "Should return the index path"
    meta_path = Path(f"{index_path}.meta.json")
    assert meta_path.exists() or Path(index_path).exists(), "Index should be created"


def test_build_index_with_metadata_template_empty_documents():
    """Test with empty documents should raise ValueError."""
    with pytest.raises(ValueError, match="documents list cannot be empty"):
        build_index_with_metadata_template([], "/tmp/test.leann")
