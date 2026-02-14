# function_implementation_file

from leann.cli import LeannCLI


def parse_cli_search_command(args_list):
    """Parse CLI arguments for the search command.
    
    Args:
        args_list: List of command line arguments to parse
        Example: ["search", "my-index", "python programming", "--top-k", "10"]
        
    Returns:
        Parsed arguments object containing command, index_name, query, and other search options
    """
    cli = LeannCLI()
    parser = cli.create_parser()
    args = parser.parse_args(args_list)
    return args

