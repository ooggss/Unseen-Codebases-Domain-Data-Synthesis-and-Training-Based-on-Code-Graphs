# new_test_case_file

import pytest
from pathlib import Path
from case12 import build_multiple_indexes, unified_search_across_indexes
from leann.api import SearchResult
import shutil


def test_build_multiple_indexes(tmp_path):
    """Test building multiple indexes from different configurations."""
    base_dir = str(tmp_path / "indexes")
    
    index_configs = [
        {
            'index_name': 'tech_docs',
            'documents': [
                {'text': 'Python is a programming language', 'metadata': {'category': 'tech', 'topic': 'programming'}},
                {'text': 'JavaScript is used for web development', 'metadata': {'category': 'tech', 'topic': 'web'}},
            ],
            'backend_name': 'hnsw'
        },
        {
            'index_name': 'science_docs',
            'documents': [
                {'text': 'Machine learning uses algorithms', 'metadata': {'category': 'science', 'topic': 'AI'}},
                {'text': 'Neural networks are computational models', 'metadata': {'category': 'science', 'topic': 'AI'}},
            ]
        }
    ]
    
    index_paths = build_multiple_indexes(index_configs, base_dir)
    
    # Verify both indexes were created
    assert len(index_paths) == 2, "Should create 2 indexes"
    assert 'tech_docs' in index_paths, "Should have tech_docs index"
    assert 'science_docs' in index_paths, "Should have science_docs index"
    
    # Verify index files exist
    # Note: build_index may create multiple files (.leann, .meta.json, .passages.jsonl, etc.)
    # The main index file (.leann) might not exist, but metadata file should exist
    for index_name, index_path in index_paths.items():
        index_path_obj = Path(index_path)
        # Check if index file exists or if metadata file exists (both indicate successful build)
        meta_path = index_path_obj.parent / f"{index_path_obj.name}.meta.json"
        assert meta_path.exists() or index_path_obj.exists(), \
            f"Either index file or metadata file should exist for {index_name}. " \
            f"Checked: {index_path}, {meta_path}"


def test_build_multiple_indexes_empty_config():
    """Test building with empty configs should raise ValueError."""
    with pytest.raises(ValueError, match="cannot be empty"):
        build_multiple_indexes([], "/tmp/test")


def test_build_multiple_indexes_missing_fields(tmp_path):
    """Test building with missing required fields should raise ValueError."""
    base_dir = str(tmp_path / "indexes")
    
    # Missing index_name
    with pytest.raises(ValueError, match="index_name"):
        build_multiple_indexes([{'documents': []}], base_dir)
    
    # Missing documents
    with pytest.raises(ValueError, match="documents"):
        build_multiple_indexes([{'index_name': 'test'}], base_dir)


def test_unified_search_across_indexes(tmp_path):
    """Test unified search across multiple indexes."""
    base_dir = tmp_path / "indexes"
    base_dir.mkdir()
    
    # Build two indexes
    index_configs = [
        {
            'index_name': 'index1',
            'documents': [
                {'text': 'Python programming language', 'metadata': {'id': '1'}},
                {'text': 'Machine learning algorithms', 'metadata': {'id': '2'}},
            ]
        },
        {
            'index_name': 'index2',
            'documents': [
                {'text': 'Python web frameworks', 'metadata': {'id': '3'}},
                {'text': 'Deep learning neural networks', 'metadata': {'id': '4'}},
            ]
        }
    ]
    
    index_paths = build_multiple_indexes(index_configs, str(base_dir))
    
    # Search across all indexes
    results = unified_search_across_indexes(index_paths, 'Python', top_k_per_index=2, global_top_k=3)
    
    # Verify results
    assert len(results) > 0, "Should return at least one result"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"
    
    # Check that results are sorted by score (descending)
    scores = [r.score for r in results]
    assert scores == sorted(scores, reverse=True), "Results should be sorted by score descending"
    
    # Check deduplication - no duplicate texts
    texts = [r.text for r in results]
    assert len(texts) == len(set(texts)), "Results should be deduplicated by text"
    
    # Check source_index metadata
    for result in results:
        assert 'source_index' in result.metadata, "Results should have source_index metadata"
        assert result.metadata['source_index'] in index_paths, "source_index should match an index name"


def test_unified_search_partial_failure(tmp_path):
    """Test unified search when one index fails."""
    base_dir = tmp_path / "indexes"
    base_dir.mkdir()
    
    # Build one valid index
    index_configs = [
        {
            'index_name': 'valid_index',
            'documents': [
                {'text': 'Test content', 'metadata': {'id': '1'}},
            ]
        }
    ]
    
    index_paths = build_multiple_indexes(index_configs, str(base_dir))
    
    # Add a non-existent index path
    index_paths['invalid_index'] = '/nonexistent/path.leann'
    
    # Should still work with valid indexes
    results = unified_search_across_indexes(index_paths, 'Test', top_k_per_index=1)
    
    # Should have results from valid index
    assert len(results) > 0, "Should return results from valid index"
    assert all(r.metadata.get('source_index') == 'valid_index' for r in results), "All results should be from valid index"
