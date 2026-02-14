# new_test_case_file

import pytest
from pathlib import Path
from case24 import get_passages_by_metadata_range
from leann.api import LeannBuilder
import shutil


def test_get_passages_by_metadata_range(tmp_path):
    """Test retrieving passages by metadata range."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Content with rating 3", metadata={"rating": 3.0, "category": "tech"})
    builder.add_text("Content with rating 4", metadata={"rating": 4.0, "category": "tech"})
    builder.add_text("Content with rating 5", metadata={"rating": 5.0, "category": "tech"})
    builder.add_text("Content with rating 2", metadata={"rating": 2.0, "category": "web"})
    builder.build_index(index_path)
    
    # Get passages with rating between 3.5 and 5.0
    passages = get_passages_by_metadata_range(index_path, "rating", 3.5, 5.0)
    
    assert len(passages) >= 1, "Should find at least one passage in range"
    assert all(3.5 <= p.get("metadata", {}).get("rating", 0) <= 5.0 for p in passages), \
        "All passages should have rating in range"


def test_get_passages_by_metadata_range_inclusive(tmp_path):
    """Test that range boundaries are inclusive."""
    index_path = str(tmp_path / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Content with rating 3", metadata={"rating": 3.0})
    builder.add_text("Content with rating 4", metadata={"rating": 4.0})
    builder.add_text("Content with rating 5", metadata={"rating": 5.0})
    builder.build_index(index_path)
    
    # Get passages with rating exactly at boundaries
    passages = get_passages_by_metadata_range(index_path, "rating", 3.0, 5.0)
    
    assert len(passages) >= 3, "Should include passages at boundaries"
    ratings = [p.get("metadata", {}).get("rating") for p in passages]
    assert 3.0 in ratings, "Should include min boundary"
    assert 5.0 in ratings, "Should include max boundary"


def test_get_passages_by_metadata_range_invalid():
    """Test with invalid range should raise ValueError."""
    with pytest.raises(ValueError, match="min_value must be less than or equal to max_value"):
        get_passages_by_metadata_range("/tmp/test.leann", "rating", 5.0, 3.0)
