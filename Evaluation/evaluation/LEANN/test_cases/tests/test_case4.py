# new_test_case_file

import pytest
from case4 import filter_search_results_by_metadata
from leann.api import SearchResult


def test_filter_search_results_by_metadata_equals():
    """Test filtering search results with equals operator."""
    # Create mock search results
    results = [
        SearchResult(id="1", score=0.9, text="Python programming", metadata={"topic": "programming", "language": "Python"}),
        SearchResult(id="2", score=0.8, text="Machine learning", metadata={"topic": "ML", "language": "Python"}),
        SearchResult(id="3", score=0.7, text="JavaScript web dev", metadata={"topic": "programming", "language": "JavaScript"}),
    ]
    
    # Filter by topic == "programming"
    filters = {"topic": {"==": "programming"}}
    filtered = filter_search_results_by_metadata(results, filters)
    
    # Should return 2 results (id 1 and 3)
    assert len(filtered) == 2, "Should return 2 results"
    assert all(r.metadata.get("topic") == "programming" for r in filtered), "All results should have topic == 'programming'"
    assert filtered[0].id in ["1", "3"], "Should include result 1 or 3"
    assert filtered[1].id in ["1", "3"], "Should include result 1 or 3"


def test_filter_search_results_by_metadata_in():
    """Test filtering search results with 'in' operator."""
    results = [
        SearchResult(id="1", score=0.9, text="Python", metadata={"language": "Python", "year": 2020}),
        SearchResult(id="2", score=0.8, text="JavaScript", metadata={"language": "JavaScript", "year": 2021}),
        SearchResult(id="3", score=0.7, text="Java", metadata={"language": "Java", "year": 2022}),
    ]
    
    # Filter by language in ["Python", "JavaScript"]
    filters = {"language": {"in": ["Python", "JavaScript"]}}
    filtered = filter_search_results_by_metadata(results, filters)
    
    # Should return 2 results
    assert len(filtered) == 2, "Should return 2 results"
    assert all(r.metadata.get("language") in ["Python", "JavaScript"] for r in filtered), "All results should be Python or JavaScript"


def test_filter_search_results_by_metadata_no_filters():
    """Test filtering with no filters should return all results."""
    results = [
        SearchResult(id="1", score=0.9, text="Test 1", metadata={"topic": "A"}),
        SearchResult(id="2", score=0.8, text="Test 2", metadata={"topic": "B"}),
    ]
    
    filtered = filter_search_results_by_metadata(results, None)
    
    # Should return all results unchanged
    assert len(filtered) == len(results), "Should return all results when no filters"
    assert filtered == results, "Results should be unchanged"


def test_filter_search_results_by_metadata_multiple_filters():
    """Test filtering with multiple filter criteria (AND logic)."""
    results = [
        SearchResult(id="1", score=0.9, text="Python AI", metadata={"topic": "AI", "language": "Python"}),
        SearchResult(id="2", score=0.8, text="Python web", metadata={"topic": "web", "language": "Python"}),
        SearchResult(id="3", score=0.7, text="JavaScript AI", metadata={"topic": "AI", "language": "JavaScript"}),
    ]
    
    # Filter by topic == "AI" AND language == "Python"
    filters = {"topic": {"==": "AI"}, "language": {"==": "Python"}}
    filtered = filter_search_results_by_metadata(results, filters)
    
    # Should return only result 1
    assert len(filtered) == 1, "Should return exactly 1 result"
    assert filtered[0].id == "1", "Should return result 1"
    assert filtered[0].metadata["topic"] == "AI", "Result should have topic == 'AI'"
    assert filtered[0].metadata["language"] == "Python", "Result should have language == 'Python'"

