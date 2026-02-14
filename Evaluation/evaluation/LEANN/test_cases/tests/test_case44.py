# new_test_case_file

import pytest
from pathlib import Path
from case44 import get_index_statistics, analyze_index_coverage
from leann.api import LeannBuilder
import shutil


def test_get_index_statistics_and_analyze_coverage(tmp_path):
    """Test getting index statistics and analyzing coverage."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "rating": 5, "author": "John"})
    builder.add_text("JavaScript guide", metadata={"category": "tech", "rating": 4})
    builder.add_text("Web design", metadata={"category": "web", "rating": 3, "author": "Jane"})
    builder.build_index(index_path)
    
    # Get statistics
    stats = get_index_statistics(index_path)
    
    assert stats["total_passages"] > 0, "Should have passages"
    assert "metadata_fields" in stats, "Should have metadata_fields"
    assert "field_value_counts" in stats, "Should have field_value_counts"
    assert "category" in stats["metadata_fields"], "Should have category field"
    
    # Analyze coverage
    coverage = analyze_index_coverage(index_path, ["category", "rating"])
    
    assert "coverage_percentage" in coverage, "Should have coverage_percentage"
    assert "field_coverage" in coverage, "Should have field_coverage"
    assert "missing_fields" in coverage, "Should have missing_fields"
    assert coverage["coverage_percentage"] > 0, "Should have some coverage"
    assert "category" in coverage["field_coverage"], "Should analyze category field"
