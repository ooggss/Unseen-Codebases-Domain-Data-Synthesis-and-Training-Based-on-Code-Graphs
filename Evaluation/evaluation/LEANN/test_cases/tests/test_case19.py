
import pytest
from pathlib import Path
from case19 import filter_passages_by_metadata_criteria
from leann.api import LeannBuilder
import shutil

def test_filter_passages_by_metadata_criteria(tmp_path):
    """Test filtering passages by metadata criteria."""
    index_dir = tmp_path / "test_index5"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index5.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Tech content 1", metadata={"id": "p1", "category": "tech", "rating": 5.0})
    builder.add_text("Tech content 2", metadata={"id": "p2", "category": "tech", "rating": 4.0})
    builder.add_text("Web content", metadata={"id": "p3", "category": "web", "rating": 5.0})
    builder.build_index(index_path)
    
    # Filter by category
    criteria = {"category": "tech"}
    matching = filter_passages_by_metadata_criteria(index_path, criteria)
    
    assert len(matching) >= 2, "Should find at least 2 tech passages"
    assert all(p.get("metadata", {}).get("category") == "tech" for p in matching), "All results should be tech"
    
    # Filter by multiple criteria
    criteria2 = {"category": "tech", "rating": 5.0}
    matching2 = filter_passages_by_metadata_criteria(index_path, criteria2)
    
    assert len(matching2) >= 1, "Should find at least 1 tech passage with rating 5.0"
    assert all(p.get("metadata", {}).get("rating") == 5.0 for p in matching2), "All results should have rating 5.0"
    
    shutil.rmtree(index_dir)


def test_filter_passages_by_metadata_no_matches(tmp_path):
    """Test filtering with criteria that match no passages."""
    index_dir = tmp_path / "test_index6"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index6.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Content", metadata={"id": "p1", "category": "tech"})
    builder.build_index(index_path)
    
    criteria = {"category": "nonexistent"}
    matching = filter_passages_by_metadata_criteria(index_path, criteria)
    
    assert matching == [], "Should return empty list for no matches"
    
    shutil.rmtree(index_dir)