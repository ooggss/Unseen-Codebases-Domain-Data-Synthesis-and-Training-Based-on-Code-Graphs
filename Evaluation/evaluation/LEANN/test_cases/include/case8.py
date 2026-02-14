# function_implementation_file

from leann.cli import LeannCLI


def remove_index_by_name(index_name: str, force: bool = False) -> bool:
    """Remove a LEANN index by name.
    
    Args:
        index_name: Name of the index to remove
        force: If True, skip confirmation prompts (default: False)
        
    Returns:
        True if removal was successful, False otherwise
    """
    cli = LeannCLI()
    result = cli.remove_index(index_name, force=force)
    return result

