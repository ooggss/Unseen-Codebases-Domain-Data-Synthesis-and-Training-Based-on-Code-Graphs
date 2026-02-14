# new_test_case_file

import pytest
import numpy as np
from case60 import compute_text_similarity_matrix


def test_compute_text_similarity_matrix():
    """Test computing text similarity matrix."""
    texts = [
        "Python programming language",
        "Python is used for software development",
        "Machine learning algorithms"
    ]
    
    matrix = compute_text_similarity_matrix(texts)
    
    assert isinstance(matrix, np.ndarray), "Should return numpy array"
    assert matrix.shape == (3, 3), "Should have correct shape"
    assert np.allclose(matrix, matrix.T), "Matrix should be symmetric"
    # Check that all values are in valid range [-1, 1] (with small tolerance for floating point)
    assert np.all(matrix >= -1.0) and np.all(matrix <= 1.0), "Similarities should be in [-1, 1]"


def test_compute_text_similarity_matrix_empty():
    """Test with empty texts should raise ValueError."""
    with pytest.raises(ValueError, match="texts list cannot be empty"):
        compute_text_similarity_matrix([])
