# new_test_case_file

import pytest
import numpy as np
from case14 import compute_embeddings_with_config


def test_compute_embeddings_with_config_basic():
    """Test basic embedding computation with default config."""
    texts = ["This is a test sentence.", "Another test sentence."]
    
    embeddings = compute_embeddings_with_config(texts)
    
    assert isinstance(embeddings, np.ndarray), "Should return numpy array"
    assert embeddings.shape[0] == len(texts), "Should have one row per text"
    assert embeddings.shape[1] > 0, "Should have embedding dimension > 0"


def test_compute_embeddings_with_config_custom_mode():
    """Test embedding computation with custom mode."""
    texts = ["Test sentence"]
    
    embeddings = compute_embeddings_with_config(
        texts,
        model_name="facebook/contriever",
        mode="sentence-transformers"
    )
    
    assert isinstance(embeddings, np.ndarray), "Should return numpy array"
    assert embeddings.shape[0] == 1, "Should have one row for one text"


def test_compute_embeddings_with_config_embedding_options():
    """Test embedding computation with embedding options."""
    texts = ["Test sentence"]
    
    embedding_options = {
        "prompt_template": "query: {}"
    }
    
    embeddings = compute_embeddings_with_config(
        texts,
        embedding_options=embedding_options
    )
    
    assert isinstance(embeddings, np.ndarray), "Should return numpy array"


def test_compute_embeddings_with_config_empty_texts():
    """Test embedding computation with empty texts should raise ValueError."""
    with pytest.raises(ValueError, match="cannot be empty"):
        compute_embeddings_with_config([])


def test_compute_embeddings_with_config_invalid_mode():
    """Test embedding computation with invalid mode should raise ValueError."""
    texts = ["Test"]
    
    with pytest.raises(ValueError, match="mode must be one of"):
        compute_embeddings_with_config(texts, mode="invalid_mode")


def test_compute_embeddings_with_config_cache():
    """Test embedding computation with caching enabled."""
    texts1 = ["Cache test sentence"]
    texts2 = ["Cache test sentence"]  # Same text
    
    # First computation
    embeddings1 = compute_embeddings_with_config(texts1, use_cache=True)
    
    # Second computation (should use cache if working)
    embeddings2 = compute_embeddings_with_config(texts2, use_cache=True)
    
    assert isinstance(embeddings1, np.ndarray), "Should return numpy array"
    assert isinstance(embeddings2, np.ndarray), "Should return numpy array"
    assert embeddings1.shape == embeddings2.shape, "Should have same shape"

