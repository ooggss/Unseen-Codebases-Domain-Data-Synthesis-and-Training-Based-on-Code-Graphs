# new_test_case_file

import pytest
from case25 import compute_similarity_between_texts


def test_compute_similarity_between_texts():
    """Test computing similarity between two texts."""
    similarity = compute_similarity_between_texts(
        "Python is a programming language",
        "Python programming is used for software development"
    )
    
    assert isinstance(similarity, float), "Should return a float"
    assert -1.0 <= similarity <= 1.0, "Similarity should be in range [-1, 1]"
    assert similarity > 0, "Similar texts should have positive similarity"


def test_compute_similarity_between_texts_same_text():
    """Test similarity between identical texts."""
    text = "Machine learning uses algorithms"
    similarity = compute_similarity_between_texts(text, text)
    
    assert similarity > 0.9, "Identical texts should have very high similarity"


def test_compute_similarity_between_texts_different():
    """Test similarity between very different texts."""
    similarity = compute_similarity_between_texts(
        "Python programming",
        "Cooking recipes"
    )
    
    assert isinstance(similarity, float), "Should return a float"
    assert -1.0 <= similarity <= 1.0, "Similarity should be in range [-1, 1]"


def test_compute_similarity_between_texts_empty():
    """Test with empty text should raise ValueError."""
    with pytest.raises(ValueError, match="Both texts must be non-empty"):
        compute_similarity_between_texts("", "test")
