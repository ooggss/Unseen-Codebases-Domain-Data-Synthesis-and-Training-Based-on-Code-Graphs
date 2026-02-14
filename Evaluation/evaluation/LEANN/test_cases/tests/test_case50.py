# new_test_case_file

import pytest
from pathlib import Path
from case50 import search_with_result_reranking
from leann.api import LeannBuilder, SearchResult
import shutil


def test_search_with_result_reranking(tmp_path):
    """Test search with result reranking."""
    index_path = str(tmp_path / "test_index.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"priority": 5, "category": "tech"})
    builder.add_text("Python basics", metadata={"priority": 3, "category": "tech"})
    builder.add_text("JavaScript guide", metadata={"priority": 4, "category": "web"})
    builder.build_index(index_path)
    
    # Rerank by priority field
    results = search_with_result_reranking(index_path, "programming", "priority", top_k=5)
    
    assert len(results) > 0, "Should return results"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"


def test_search_with_result_reranking_custom_function(tmp_path):
    """Test reranking with custom function."""
    index_path = str(tmp_path / "test_index2.leann")
    
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"rating": 5})
    builder.build_index(index_path)
    
    def custom_rerank(field_value, original_score):
        if isinstance(field_value, (int, float)):
            return original_score * (1 + field_value / 10)
        return original_score
    
    results = search_with_result_reranking(index_path, "Python", "rating", rerank_function=custom_rerank, top_k=5)
    
    assert len(results) > 0, "Should return reranked results"
