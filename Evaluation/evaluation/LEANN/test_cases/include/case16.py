# function_implementation_file

from typing import List, Dict, Any, Optional
from leann.cli import LeannCLI
from leann.api import LeannBuilder, LeannSearcher
from pathlib import Path


def parse_and_build_index_from_cli_args(
    args_list: List[str],
    output_index_path: Optional[str] = None
) -> str:
    """Parse CLI build arguments and execute index building via API.
    
    Args:
        args_list: List of command line arguments, starting with 'build' command.
            Example: ["build", "my-index", "--docs", "./docs", "--backend-name", "hnsw"]
        output_index_path: Optional custom output path. If None, uses CLI default location.
        
    Returns:
        Path to the built index file
        
    Raises:
        ValueError: If args_list doesn't start with 'build' or if required arguments are missing
    """
    if not args_list or args_list[0] != "build":
        raise ValueError("args_list must start with 'build' command")
    
    # Create CLI parser
    cli = LeannCLI()
    parser = cli.create_parser()
    
    # Parse arguments
    args = parser.parse_args(args_list)
    
    # Validate parsed arguments
    if args.command != "build":
        raise ValueError(f"Expected 'build' command, got '{args.command}'")
    
    # Determine index path
    if output_index_path:
        index_path = output_index_path
    else:
        # Use CLI's default path logic
        index_name = args.index_name if args.index_name else Path.cwd().name
        index_path = cli.get_index_path(index_name)
        # Ensure parent directory exists
        Path(index_path).parent.mkdir(parents=True, exist_ok=True)
    
    # Extract build parameters
    backend_name = args.backend_name
    docs_paths = args.docs
    
    # Build index using API (not CLI async method)
    builder = LeannBuilder(backend_name=backend_name)
    
    # Load documents using CLI's document loading method
    # Note: args should be the parsed argparse.Namespace object
    all_texts = cli.load_documents(
        docs_paths=docs_paths,
        custom_file_types=getattr(args, 'file_types', None),
        include_hidden=getattr(args, 'include_hidden', False),
        args=args
    )
    
    if not all_texts:
        raise ValueError("No documents found to index")
    
    # Add all texts to builder
    for chunk in all_texts:
        text = chunk.get("text", "")
        metadata = chunk.get("metadata", {})
        builder.add_text(text, metadata=metadata)
    
    # Build the index
    builder.build_index(index_path)
    
    return index_path


def parse_and_search_from_cli_args(
    args_list: List[str]
) -> List[Any]:
    """Parse CLI search arguments and execute search via API.
    
    Args:
        args_list: List of command line arguments, starting with 'search' command.
            Example: ["search", "my-index", "python programming", "--top-k", "10"]
        
    Returns:
        List of SearchResult objects
        
    Raises:
        ValueError: If args_list doesn't start with 'search' or if required arguments are missing
    """
    if not args_list or args_list[0] != "search":
        raise ValueError("args_list must start with 'search' command")
    
    # Create CLI parser
    cli = LeannCLI()
    parser = cli.create_parser()
    
    # Parse arguments - catch SystemExit from argparse when required arguments are missing
    import sys
    try:
        args = parser.parse_args(args_list)
    except SystemExit as e:
        # argparse calls sys.exit(2) when required arguments are missing
        # Convert this to ValueError for better error handling
        if e.code == 2:
            raise ValueError("query is required for search command") from None
        raise
    
    # Validate parsed arguments
    if args.command != "search":
        raise ValueError(f"Expected 'search' command, got '{args.command}'")
    
    if not args.index_name:
        raise ValueError("index_name is required for search command")
    # Check if query is None or empty string
    if not hasattr(args, 'query') or args.query is None or (isinstance(args.query, str) and not args.query.strip()):
        raise ValueError("query is required for search command")
    
    # Get index path
    index_path = cli.get_index_path(args.index_name)
    
    if not cli.index_exists(args.index_name):
        raise FileNotFoundError(f"Index '{args.index_name}' not found at {index_path}")
    
    # Create searcher and perform search
    searcher = LeannSearcher(index_path=index_path)
    
    results = searcher.search(
        query=args.query,
        top_k=args.top_k,
        complexity=args.complexity if hasattr(args, 'complexity') else 64
    )
    
    return results
