# new_test_case_file

import pytest
from case11 import parse_cli_search_command


def test_parse_cli_search_command_basic(tmp_path, monkeypatch):
    """Test parsing basic search command."""
    monkeypatch.chdir(tmp_path)
    
    args_list = ["search", "my-index", "python programming"]
    
    args = parse_cli_search_command(args_list)
    
    # Verify parsed arguments
    assert args.command == "search", "Command should be 'search'"
    assert args.index_name == "my-index", "Index name should be parsed correctly"
    assert args.query == "python programming", "Query should be parsed correctly"


def test_parse_cli_search_command_with_options(tmp_path, monkeypatch):
    """Test parsing search command with additional options."""
    monkeypatch.chdir(tmp_path)
    
    args_list = ["search", "my-index", "machine learning", "--top-k", "10", "--complexity", "128"]
    
    args = parse_cli_search_command(args_list)
    
    # Verify parsed arguments
    assert args.command == "search"
    assert args.index_name == "my-index"
    assert args.query == "machine learning"
    assert args.top_k == 10, "top-k option should be parsed"
    assert args.complexity == 128, "complexity option should be parsed"


def test_parse_cli_search_command_with_metadata_flag(tmp_path, monkeypatch):
    """Test parsing search command with --show-metadata flag."""
    monkeypatch.chdir(tmp_path)
    
    args_list = ["search", "my-index", "query text", "--show-metadata"]
    
    args = parse_cli_search_command(args_list)
    
    assert args.command == "search"
    assert args.index_name == "my-index"
    assert args.query == "query text"
    assert args.show_metadata is True, "show_metadata flag should be set"

