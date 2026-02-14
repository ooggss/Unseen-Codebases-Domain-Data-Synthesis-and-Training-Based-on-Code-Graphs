# function_implementation_file

from leann.cli import LeannCLI


def list_all_indexes():
    """List all available LEANN indexes in the current project and other registered projects.
    
    Returns:
        None (prints the list to stdout)
    """
    cli = LeannCLI()
    cli.list_indexes()

