# new_test_case_file

from pathlib import Path
from case2 import build_document_index


def test_build_document_index(tmp_path):
    """Test building an index from a list of documents with metadata."""
    
    documents = [
        {
            "text": "Python is a high-level programming language known for its simplicity and readability.",
            "metadata": {"id": "doc1", "title": "Python Introduction", "author": "John Doe"}
        },
        {
            "text": "Machine learning is a subset of artificial intelligence that enables systems to learn from data.",
            "metadata": {"id": "doc2", "title": "Machine Learning Basics", "author": "Jane Smith"}
        },
        {
            "text": "Vector databases are specialized databases designed to store and query high-dimensional vectors efficiently.",
            "metadata": {"id": "doc3", "title": "Vector Databases", "author": "Bob Johnson"}
        }
    ]
    
    index_path = str(tmp_path / "test_index.leann")
    
    result_path = build_document_index(documents, index_path, backend_name="hnsw")
    
    # Verify the index was created (check for .leann or .index file)
    base_path = Path(index_path)
    index_exists = base_path.exists() or base_path.with_suffix('.index').exists()
    assert index_exists, "Index file should be created (.leann or .index)"
    
    # Verify metadata file exists
    meta_path = Path(index_path).parent / f"{Path(index_path).name}.meta.json"
    assert meta_path.exists(), "Metadata file should be created"
    
    # Verify the returned path matches
    assert result_path == index_path, "Returned path should match the input path"
    
    # Verify passages file exists
    passages_path = Path(index_path).parent / f"{Path(index_path).name}.passages.jsonl"
    assert passages_path.exists(), "Passages file should be created"

