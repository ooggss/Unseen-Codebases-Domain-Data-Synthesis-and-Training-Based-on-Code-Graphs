# new_test_case_file

import pytest
import numpy as np
from case5 import compute_text_embeddings


def test_compute_text_embeddings_single_text():
    """Test computing embeddings for a single text."""
    texts = ["This is a test sentence."]
    
    embeddings = compute_text_embeddings(texts)
    
    # Verify output
    assert isinstance(embeddings, np.ndarray), "Should return numpy array"
    assert embeddings.shape[0] == 1, "Should have one row for one text"
    assert embeddings.shape[1] > 0, "Should have embedding dimension > 0"
    assert embeddings.dtype in (np.float16, np.float32, np.float64), "Should be float array"


def test_compute_text_embeddings_multiple_texts():
    """Test computing embeddings for multiple texts."""
    texts = [
        "Python is a programming language.",
        "Machine learning uses algorithms.",
        "Vector databases store embeddings."
    ]
    
    embeddings = compute_text_embeddings(texts)
    
    # Verify output
    assert isinstance(embeddings, np.ndarray), "Should return numpy array"
    assert embeddings.shape[0] == len(texts), "Should have one row per text"
    assert embeddings.shape[1] > 0, "Should have embedding dimension > 0"
    
    # Verify all embeddings have same dimension
    assert all(embeddings.shape[1] == embeddings[i].shape[0] for i in range(len(texts))), "All embeddings should have same dimension"


def test_compute_text_embeddings_empty_list():
    """Test computing embeddings for empty list should raise error or return empty array."""
    texts = []
    
    # Should handle empty list gracefully (may raise error or return empty array)
    try:
        embeddings = compute_text_embeddings(texts)
        assert embeddings.shape[0] == 0, "If no error, should return empty array"
    except (ValueError, IndexError):
        # It's acceptable to raise an error for empty input
        pass


def test_compute_text_embeddings_different_models_same_dimension():
    """Test that different texts produce different embeddings."""
    texts = [
        "Python programming language",
        "Completely different topic here"
    ]
    
    embeddings = compute_text_embeddings(texts)
    
    # Verify embeddings are different (different texts should have different embeddings)
    assert not np.allclose(embeddings[0], embeddings[1]), "Different texts should produce different embeddings"

