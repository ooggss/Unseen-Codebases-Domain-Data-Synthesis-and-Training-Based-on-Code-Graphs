# new_test_case_file

import pytest
from case36 import find_most_similar_text


def test_find_most_similar_text():
    """Test finding most similar text."""
    query = "Python programming language"
    candidates = [
        "JavaScript web development",
        "Python is used for software development",
        "Machine learning algorithms"
    ]
    
    result = find_most_similar_text(query, candidates)
    
    assert isinstance(result, dict), "Should return a dictionary"
    assert "most_similar_text" in result, "Should have most_similar_text"
    assert "similarity_score" in result, "Should have similarity_score"
    assert "index" in result, "Should have index"
    assert result["most_similar_text"] in candidates, "Most similar text should be from candidates"
    assert 0 <= result["index"] < len(candidates), "Index should be valid"
    assert -1.0 <= result["similarity_score"] <= 1.0, "Similarity score should be in valid range"


def test_find_most_similar_text_empty_query():
    """Test with empty query should raise ValueError."""
    with pytest.raises(ValueError, match="query_text cannot be empty"):
        find_most_similar_text("", ["candidate"])


def test_find_most_similar_text_empty_candidates():
    """Test with empty candidates should raise ValueError."""
    with pytest.raises(ValueError, match="candidate_texts cannot be empty"):
        find_most_similar_text("query", [])
