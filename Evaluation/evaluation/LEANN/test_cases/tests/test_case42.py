# new_test_case_file

import pytest
from pathlib import Path
from case42 import add_documents_to_existing_index, rebuild_index_if_needed
from leann.api import LeannBuilder
import shutil


def test_add_documents_to_existing_index(tmp_path):
    """Test adding documents to existing index and checking if rebuild is needed."""
    index_path = str(tmp_path / "test_index.leann")
    
    # Build initial index
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Original document", metadata={"id": "1"})
    builder.build_index(index_path)
    
    # Get initial passage count
    initial_check = rebuild_index_if_needed(index_path, min_passage_count=0)
    initial_count = initial_check["passage_count"]
    
    # Add new documents
    new_docs = [
        {"text": "New document 1", "metadata": {"id": "2"}},
        {"text": "New document 2", "metadata": {"id": "3"}}
    ]
    
    result = add_documents_to_existing_index(index_path, new_docs)
    
    assert result["original_passage_count"] == initial_count, "Should match initial count"
    assert result["new_passage_count"] > initial_count, "Should have more passages"
    assert result["documents_added"] == 2, "Should add 2 documents"
    
    # Check if rebuild is needed
    final_check = rebuild_index_if_needed(index_path, min_passage_count=0)
    assert final_check["passage_count"] > initial_count, "Passage count should increase"


def test_add_documents_to_existing_index_empty():
    """Test with empty documents should raise ValueError."""
    with pytest.raises(ValueError, match="new_documents cannot be empty"):
        add_documents_to_existing_index("/tmp/test.leann", [])
