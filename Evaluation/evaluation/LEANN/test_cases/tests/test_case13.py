# new_test_case_file

import pytest
from case13 import apply_dynamic_filters
from leann.api import SearchResult


def test_apply_dynamic_filters_and_logic():
    """Test dynamic filtering with AND logic."""
    results = [
        SearchResult(id="1", score=0.9, text="Python AI", metadata={"category": "tech", "rating": 5.0}),
        SearchResult(id="2", score=0.8, text="Python web", metadata={"category": "tech", "rating": 3.0}),
        SearchResult(id="3", score=0.7, text="JavaScript AI", metadata={"category": "web", "rating": 5.0}),
    ]
    
    filters = {
        "category": {"==": "tech"},
        "rating": {">=": 4.0}
    }
    
    filtered = apply_dynamic_filters(results, filters, filter_logic="AND")
    
    # Should return only result 1 (tech AND rating >= 4.0)
    assert len(filtered) == 1, "Should return exactly 1 result with AND logic"
    assert filtered[0].id == "1", "Should return result 1"
    assert filtered[0].metadata["category"] == "tech"
    assert filtered[0].metadata["rating"] >= 4.0


def test_apply_dynamic_filters_or_logic():
    """Test dynamic filtering with OR logic."""
    results = [
        SearchResult(id="1", score=0.9, text="Python AI", metadata={"category": "tech", "rating": 5.0}),
        SearchResult(id="2", score=0.8, text="Python web", metadata={"category": "tech", "rating": 3.0}),
        SearchResult(id="3", score=0.7, text="JavaScript AI", metadata={"category": "web", "rating": 5.0}),
    ]
    
    filters = {
        "category": {"==": "tech"},
        "rating": {">=": 4.0}
    }
    
    filtered = apply_dynamic_filters(results, filters, filter_logic="OR")
    
    # Should return results 1 (tech), 2 (tech), and 3 (rating >= 4.0)
    assert len(filtered) == 3, "Should return 3 results with OR logic"
    result_ids = {r.id for r in filtered}
    assert result_ids == {"1", "2", "3"}, "Should include all results"


def test_apply_dynamic_filters_no_filters():
    """Test filtering with no filters should return all results."""
    results = [
        SearchResult(id="1", score=0.9, text="Test 1", metadata={"category": "A"}),
        SearchResult(id="2", score=0.8, text="Test 2", metadata={"category": "B"}),
    ]
    
    filtered = apply_dynamic_filters(results, {}, filter_logic="AND")
    
    assert len(filtered) == len(results), "Should return all results when no filters"
    assert filtered == results, "Results should be unchanged"


def test_apply_dynamic_filters_invalid_logic():
    """Test filtering with invalid logic should raise ValueError."""
    results = [SearchResult(id="1", score=0.9, text="Test", metadata={})]
    
    with pytest.raises(ValueError, match="must be 'AND' or 'OR'"):
        apply_dynamic_filters(results, {"field": {"==": "value"}}, filter_logic="INVALID")
