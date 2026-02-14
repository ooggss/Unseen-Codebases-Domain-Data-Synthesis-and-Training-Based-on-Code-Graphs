# new_test_case_file

import pytest
from case10 import chunk_document_text


def test_chunk_document_text_basic():
    """Test basic text chunking."""
    text = "This is a test document. " * 50  # Create a long text
    text += "It contains multiple sentences. " * 30
    
    chunks = chunk_document_text(text, chunk_size=256, chunk_overlap=128)
    
    # Verify output
    assert len(chunks) > 0, "Should produce at least one chunk"
    assert all(isinstance(chunk, dict) for chunk in chunks), "All chunks should be dictionaries"
    assert all("text" in chunk for chunk in chunks), "All chunks should have 'text' field"
    assert all("metadata" in chunk for chunk in chunks), "All chunks should have 'metadata' field"
    
    # Verify total text content is preserved (approximately)
    total_chunked_text = " ".join(chunk["text"] for chunk in chunks)
    assert len(total_chunked_text) > len(text) * 0.5, "Should preserve most of the text"


def test_chunk_document_text_short():
    """Test chunking a short text."""
    text = "This is a short text."
    
    chunks = chunk_document_text(text, chunk_size=256, chunk_overlap=128)
    
    # Short text should produce at least one chunk
    assert len(chunks) >= 1, "Should produce at least one chunk"
    assert chunks[0]["text"] == text or text in chunks[0]["text"], "Should contain the original text"


def test_chunk_document_text_custom_params():
    """Test chunking with custom chunk size and overlap."""
    text = "Sentence one. Sentence two. Sentence three. " * 20
    
    chunks_small = chunk_document_text(text, chunk_size=128, chunk_overlap=32)
    chunks_large = chunk_document_text(text, chunk_size=512, chunk_overlap=128)
    
    # Smaller chunk size should produce more chunks
    assert len(chunks_small) >= len(chunks_large), "Smaller chunk size should produce more chunks"

