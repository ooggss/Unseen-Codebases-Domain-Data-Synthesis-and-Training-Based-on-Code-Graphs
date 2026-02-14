# new_test_case_file

import pytest
from pathlib import Path
from case34 import search_and_aggregate_scores
from leann.api import LeannBuilder
import shutil


def test_search_and_aggregate_scores(tmp_path):
    """Test search and score aggregation."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech"})
    builder.add_text("JavaScript guide", metadata={"category": "tech"})
    builder.add_text("Web design", metadata={"category": "web"})
    builder.build_index(index_path)
    
    aggregated = search_and_aggregate_scores(index_path, "programming", "category", top_k=10)
    
    assert isinstance(aggregated, dict), "Should return a dictionary"
    assert len(aggregated) > 0, "Should have at least one aggregation"
    
    # Check structure
    for field_value, stats in aggregated.items():
        assert "count" in stats, "Should have count"
        assert "avg_score" in stats, "Should have avg_score"
        assert "max_score" in stats, "Should have max_score"
        assert "min_score" in stats, "Should have min_score"
        assert stats["count"] > 0, "Count should be positive"
