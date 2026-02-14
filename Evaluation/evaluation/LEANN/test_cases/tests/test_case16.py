# new_test_case_file

import pytest
from pathlib import Path
from case16 import parse_and_build_index_from_cli_args, parse_and_search_from_cli_args
from leann.api import SearchResult
import tempfile
import os


def test_parse_and_build_index_from_cli_args(tmp_path, monkeypatch):
    """Test parsing CLI build args and building index via API."""
    monkeypatch.chdir(tmp_path)
    
    # Create test document directory
    docs_dir = tmp_path / "test_docs"
    docs_dir.mkdir()
    (docs_dir / "doc1.txt").write_text("Python is a programming language.")
    (docs_dir / "doc2.txt").write_text("Machine learning uses algorithms.")
    
    # CLI args
    args_list = [
        "build",
        "test-index",
        "--docs", str(docs_dir),
        "--backend-name", "hnsw"
    ]
    
    index_path = parse_and_build_index_from_cli_args(args_list)
    
    # Verify index was created - check metadata file as build_index creates multiple files
    index_path_obj = Path(index_path)
    meta_path = index_path_obj.parent / f"{index_path_obj.name}.meta.json"
    # Either the main index file or metadata file should exist to indicate successful build
    assert meta_path.exists() or index_path_obj.exists(), \
        f"Either index file or metadata file should exist. Checked: {index_path}, {meta_path}"


def test_parse_and_build_index_from_cli_args_custom_path(tmp_path, monkeypatch):
    """Test building index with custom output path."""
    monkeypatch.chdir(tmp_path)
    
    docs_dir = tmp_path / "docs"
    docs_dir.mkdir()
    (docs_dir / "test.txt").write_text("Test content.")
    
    custom_path = str(tmp_path / "custom_index.leann")
    
    args_list = ["build", "test", "--docs", str(docs_dir)]
    index_path = parse_and_build_index_from_cli_args(args_list, output_index_path=custom_path)
    
    assert index_path == custom_path, "Should use custom path"
    # Verify index was created - check metadata file
    custom_path_obj = Path(custom_path)
    meta_path = custom_path_obj.parent / f"{custom_path_obj.name}.meta.json"
    assert meta_path.exists() or custom_path_obj.exists(), \
        f"Either index file or metadata file should exist at custom path. Checked: {custom_path}, {meta_path}"


def test_parse_and_build_index_from_cli_args_invalid_command():
    """Test with invalid command should raise ValueError."""
    with pytest.raises(ValueError, match="must start with 'build'"):
        parse_and_build_index_from_cli_args(["search", "index"])


def test_parse_and_search_from_cli_args(tmp_path, monkeypatch):
    """Test parsing CLI search args and executing search via API."""
    monkeypatch.chdir(tmp_path)
    
    # First build an index
    docs_dir = tmp_path / "search_docs"
    docs_dir.mkdir()
    (docs_dir / "content.txt").write_text("Python programming language.")
    
    build_args = ["build", "search-index", "--docs", str(docs_dir)]
    parse_and_build_index_from_cli_args(build_args)
    
    # Now search
    search_args = [
        "search",
        "search-index",
        "Python",
        "--top-k", "5"
    ]
    
    results = parse_and_search_from_cli_args(search_args)
    
    assert isinstance(results, list), "Should return a list"
    assert len(results) > 0, "Should return at least one result"
    assert all(isinstance(r, SearchResult) for r in results), "All results should be SearchResult objects"


def test_parse_and_search_from_cli_args_missing_query():
    """Test search with missing query should raise ValueError."""
    with pytest.raises(ValueError, match="query is required"):
        parse_and_search_from_cli_args(["search", "index-name"])


def test_parse_and_search_from_cli_args_invalid_command():
    """Test with invalid command should raise ValueError."""
    with pytest.raises(ValueError, match="must start with 'search'"):
        parse_and_search_from_cli_args(["build", "index"])


