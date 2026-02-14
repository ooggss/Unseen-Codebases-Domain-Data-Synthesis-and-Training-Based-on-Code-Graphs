# function_implementation_file

from leann.cli import LeannCLI


def parse_cli_ask_with_positional_query(args_list):
    """Parse CLI arguments for ask command with positional query.
    
    Args:
        args_list: List of command line arguments to parse
        
    Returns:
        Parsed arguments object containing command, index_name, and query
    """
    cli = LeannCLI()
    parser = cli.create_parser()
    args = parser.parse_args(args_list)
    return args

