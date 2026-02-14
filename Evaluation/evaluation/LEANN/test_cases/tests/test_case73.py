# new_test_case_file

import pytest
from pathlib import Path
from case73 import get_passages_by_multiple_criteria
from leann.api import LeannBuilder
import shutil


def test_get_passages_by_multiple_criteria(tmp_path):
    """Test retrieving passages by multiple criteria."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "rating": 5, "language": "python"})
    builder.add_text("JavaScript guide", metadata={"category": "tech", "rating": 4, "language": "javascript"})
    builder.add_text("Web design", metadata={"category": "web", "rating": 5, "language": "html"})
    builder.build_index(index_path)
    
    criteria = {"category": "tech", "rating": 5}
    passages = get_passages_by_multiple_criteria(index_path, criteria)
    
    assert len(passages) >= 1, "Should find passages matching all criteria"
    assert all(p.get("metadata", {}).get("category") == "tech" for p in passages), \
        "All passages should have category tech"
    assert all(p.get("metadata", {}).get("rating") == 5 for p in passages), \
        "All passages should have rating 5"
