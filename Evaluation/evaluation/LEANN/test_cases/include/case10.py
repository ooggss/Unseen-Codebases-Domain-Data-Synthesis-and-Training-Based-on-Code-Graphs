# function_implementation_file

from typing import List, Dict, Any
from llama_index.core.node_parser import SentenceSplitter
from llama_index.core import Document


def chunk_document_text(text: str, chunk_size: int = 256, chunk_overlap: int = 128) -> List[Dict[str, Any]]:
    """Split a document text into chunks using SentenceSplitter.
    
    Args:
        text: The document text to chunk
        chunk_size: Size of each chunk in tokens (default: 256)
        chunk_overlap: Overlap between chunks in tokens (default: 128)
        
    Returns:
        List of dictionaries, each containing 'text' and 'metadata' fields
    """
    # Create SentenceSplitter instance
    parser = SentenceSplitter(
        chunk_size=chunk_size,
        chunk_overlap=chunk_overlap,
        separator=" ",
        paragraph_separator="\n\n"
    )
    
    # Create a Document object
    doc = Document(text=text)
    
    # Split document into nodes
    nodes = parser.get_nodes_from_documents([doc])
    
    # Convert nodes to dictionaries
    chunks = []
    for node in nodes:
        chunks.append({
            "text": node.get_content(),
            "metadata": node.metadata
        })
    
    return chunks

