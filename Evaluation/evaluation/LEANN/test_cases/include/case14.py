# function_implementation_file

from typing import List, Dict, Any, Optional
import numpy as np
from leann.api import compute_embeddings
from functools import lru_cache


def compute_embeddings_with_config(
    texts: List[str],
    model_name: str = "facebook/contriever",
    mode: str = "sentence-transformers",
    embedding_options: Optional[Dict[str, Any]] = None,
    use_cache: bool = False
) -> np.ndarray:
    """Compute embeddings with custom configuration and optional caching.
    
    Args:
        texts: List of text strings to embed
        model_name: Name of the embedding model to use
        mode: Embedding backend mode ('sentence-transformers', 'mlx', 'openai', 'ollama')
        embedding_options: Optional dictionary of embedding configuration options.
            May include keys like 'provider_options', 'prompt_template', etc.
        use_cache: If True, cache embeddings for identical text strings
        
    Returns:
        NumPy array of embeddings with shape (num_texts, embedding_dimension)
        
    Raises:
        ValueError: If texts is empty or if mode is invalid
    """
    if not texts:
        raise ValueError("texts cannot be empty")
    
    valid_modes = ["sentence-transformers", "mlx", "openai", "ollama"]
    if mode not in valid_modes:
        raise ValueError(f"mode must be one of {valid_modes}, got {mode}")
    
    # Prepare provider_options if embedding_options provided
    provider_options = embedding_options if embedding_options else None
    
    # If caching is enabled, use cached computation for duplicate texts
    if use_cache:
        # Create a cache key for the computation (convert dict to frozenset of items for hashing)
        cache_key = (
            tuple(texts),
            model_name,
            mode,
            frozenset(embedding_options.items()) if embedding_options else frozenset()
        )
        result = _get_cached_result(cache_key, _cached_compute, cache_key, provider_options)
        return result
    
    # Compute embeddings directly
    embeddings = compute_embeddings(
        chunks=texts,
        model_name=model_name,
        mode=mode,
        use_server=False,
        is_build=False,
        provider_options=provider_options
    )
    
    return np.asarray(embeddings)


def _cached_compute(cache_key: tuple, provider_options: Optional[Dict[str, Any]]):
    """Internal cached computation function."""
    texts_tuple, model_name, mode, options_set = cache_key
    texts_list = list(texts_tuple)
    
    # Reconstruct embedding_options from frozenset if needed
    embedding_opts = dict(options_set) if options_set else provider_options
    
    embeddings = compute_embeddings(
        chunks=texts_list,
        model_name=model_name,
        mode=mode,
        use_server=False,
        is_build=False,
        provider_options=embedding_opts
    )
    
    return np.asarray(embeddings)


# Create a memoized version using a simpler approach
_cached_compute_memo = {}
def _get_cached_result(key, compute_func, *args, **kwargs):
    """Helper to get cached result or compute and cache it."""
    if key in _cached_compute_memo:
        return _cached_compute_memo[key]
    result = compute_func(*args, **kwargs)
    _cached_compute_memo[key] = result
    return result
