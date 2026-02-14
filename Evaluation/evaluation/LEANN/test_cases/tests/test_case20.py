import pytest
from pathlib import Path
from case20 import convert_cli_args_to_api_config
from leann.api import SearchResult
import tempfile
import os


def test_convert_cli_args_to_api_config_build():
    """Test converting build CLI args to API config."""
    args_list = [
        "build",
        "my-index",
        "--docs", "./docs",
        "--backend-name", "hnsw",
        "--embedding-model", "test-model"
    ]
    
    config = convert_cli_args_to_api_config(args_list, command_type="build")
    
    assert config["command"] == "build"
    assert config["index_name"] == "my-index"
    assert config["backend_name"] == "hnsw"
    assert config["embedding_model"] == "test-model"
    assert "./docs" in config["docs"]


def test_convert_cli_args_to_api_config_search():
    """Test converting search CLI args to API config."""
    args_list = [
        "search",
        "my-index",
        "test query",
        "--top-k", "10"
    ]
    
    config = convert_cli_args_to_api_config(args_list, command_type="search")
    
    assert config["command"] == "search"
    assert config["index_name"] == "my-index"
    assert config["query"] == "test query"
    assert config["top_k"] == 10


def test_convert_cli_args_to_api_config_invalid_type():
    """Test with invalid command type should raise ValueError."""
    with pytest.raises(ValueError, match="must be 'build' or 'search'"):
        convert_cli_args_to_api_config(["build", "index"], command_type="invalid")