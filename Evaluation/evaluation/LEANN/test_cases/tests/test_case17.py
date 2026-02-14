
import pytest
from case17 import aggregate_search_results
from leann.api import SearchResult

def test_aggregate_search_results_default():
    """Test aggregation with default functions."""
    results = [
        SearchResult(id="1", score=0.9, text="Python", metadata={"category": "tech"}),
        SearchResult(id="2", score=0.8, text="JavaScript", metadata={"category": "tech"}),
        SearchResult(id="3", score=0.7, text="React", metadata={"category": "web"}),
        SearchResult(id="4", score=0.95, text="Vue", metadata={"category": "web"}),
    ]
    
    aggregated = aggregate_search_results(results, "category")
    
    # Should have two groups: tech and web
    assert "tech" in aggregated, "Should have tech group"
    assert "web" in aggregated, "Should have web group"
    
    # Check default statistics
    tech_stats = aggregated["tech"]
    assert tech_stats["count"] == 2, "Tech group should have 2 results"
    assert tech_stats["avg_score"] == pytest.approx(0.85, abs=0.01), "Tech avg_score should be 0.85"
    assert tech_stats["max_score"] == 0.9, "Tech max_score should be 0.9"
    assert tech_stats["min_score"] == 0.8, "Tech min_score should be 0.8"
    
    web_stats = aggregated["web"]
    assert web_stats["count"] == 2, "Web group should have 2 results"


def test_aggregate_search_results_custom_funcs():
    """Test aggregation with custom aggregation functions."""
    results = [
        SearchResult(id="1", score=0.9, text="Python", metadata={"category": "tech"}),
        SearchResult(id="2", score=0.8, text="JavaScript", metadata={"category": "tech"}),
    ]
    
    def custom_count(results):
        return len(results) * 2
    
    aggregation_funcs = {
        "custom_count": custom_count,
        "total_score": lambda results: sum(r.score for r in results)
    }
    
    aggregated = aggregate_search_results(results, "category", aggregation_funcs)
    
    tech_stats = aggregated["tech"]
    assert tech_stats["custom_count"] == 4, "Custom count should be 4 (2 * 2)"
    assert tech_stats["total_score"] == pytest.approx(1.7, abs=0.01), "Total score should be 1.7"


def test_aggregate_search_results_empty():
    """Test aggregation with empty results."""
    aggregated = aggregate_search_results([], "category")
    assert aggregated == {}, "Should return empty dict for empty results"


def test_aggregate_search_results_missing_field():
    """Test aggregation when grouping field is missing in some results."""
    results = [
        SearchResult(id="1", score=0.9, text="Python", metadata={"category": "tech"}),
        SearchResult(id="2", score=0.8, text="JavaScript", metadata={}),  # Missing category
        SearchResult(id="3", score=0.7, text="React", metadata={"category": "web"}),
    ]
    
    aggregated = aggregate_search_results(results, "category")
    
    assert "tech" in aggregated, "Should have tech group"
    assert "web" in aggregated, "Should have web group"
    assert "unknown" in aggregated, "Should have unknown group for missing field"
    assert aggregated["unknown"]["count"] == 1, "Unknown group should have 1 result"