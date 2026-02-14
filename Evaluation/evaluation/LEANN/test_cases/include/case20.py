# function_implementation_file

from typing import List, Dict, Any
from leann.cli import LeannCLI


def convert_cli_args_to_api_config(
    args_list: List[str],
    command_type: str = "build"
) -> Dict[str, Any]:
    """Convert CLI arguments to API configuration dictionary.
    
    Args:
        args_list: List of command line arguments
        command_type: Type of command ('build' or 'search')
        
    Returns:
        Dictionary containing API configuration extracted from CLI arguments
    """
    if command_type not in ["build", "search"]:
        raise ValueError("command_type must be 'build' or 'search'")
    
    # Create CLI parser
    cli = LeannCLI()
    parser = cli.create_parser()
    
    # Parse arguments
    args = parser.parse_args(args_list)
    
    config = {
        "command": args.command
    }
    
    if command_type == "build" and args.command == "build":
        config.update({
            "index_name": args.index_name,
            "docs": args.docs,
            "backend_name": args.backend_name,
            "embedding_model": args.embedding_model,
            "embedding_mode": args.embedding_mode,
            "file_types": args.file_types,
            "include_hidden": args.include_hidden if hasattr(args, 'include_hidden') else False
        })
    elif command_type == "search" and args.command == "search":
        config.update({
            "index_name": args.index_name,
            "query": args.query,
            "top_k": args.top_k,
            "complexity": args.complexity if hasattr(args, 'complexity') else 64
        })
    
    return config
