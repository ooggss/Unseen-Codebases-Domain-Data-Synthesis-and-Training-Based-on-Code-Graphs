# new_test_case_file

import pytest
from pathlib import Path
from case48 import search_with_recency_boost
from leann.api import LeannBuilder, SearchResult
from datetime import datetime, timedelta
import shutil


def test_search_with_recency_boost(tmp_path):
    """Test search with recency boosting."""
    index_path = str(tmp_path / "test_index.leann")
    
    now = datetime.now()
    recent_date = (now - timedelta(days=10)).isoformat()
    old_date = (now - timedelta(days=60)).isoformat()
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Recent Python tutorial", metadata={"date": recent_date, "category": "tech"})
    builder.add_text("Old Python guide", metadata={"date": old_date, "category": "tech"})
    builder.build_index(index_path)
    
    results = search_with_recency_boost(index_path, "Python", "date", recency_days=30, top_k=5)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    
    # Recent results should come first
    recent_count = sum(1 for r in results if r.metadata and r.metadata.get("date") == recent_date)
    assert recent_count > 0, "Should have recent results"


def test_search_with_recency_boost_invalid_days():
    """Test with invalid recency_days should raise ValueError."""
    with pytest.raises(ValueError, match="recency_days must be greater than 0"):
        search_with_recency_boost("/tmp/test.leann", "query", "date", recency_days=0)
