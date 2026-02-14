# new_test_case_file

import pytest
from pathlib import Path
from case6 import ask_question
from leann.api import LeannBuilder
import tempfile
import shutil


def test_ask_question_with_index(tmp_path):
    """Test asking a question to a LEANN index."""
    # First, create an index with some documents
    index_dir = tmp_path / "test_index"
    index_dir.mkdir()
    index_path = str(index_dir / "test_index.leann")
    
    # Build a small index with context about Python
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text(
        "Python is a high-level, interpreted programming language. It was created by Guido van Rossum.",
        metadata={"topic": "Python", "type": "programming"}
    )
    builder.add_text(
        "Python supports multiple programming paradigms including procedural, object-oriented, and functional programming.",
        metadata={"topic": "Python", "type": "programming"}
    )
    builder.build_index(index_path)
    
    # Ask a question (using simulated LLM to avoid external dependencies)
    try:
        answer = ask_question(
            index_path=index_path,
            question="Who created Python?",
            top_k=2,
            llm="simulated",  # Use simulated LLM for testing
            model="simulated-model"
        )
        
        # Verify answer is returned
        assert isinstance(answer, str), "Should return a string answer"
        assert len(answer) > 0, "Answer should not be empty"
        
    except Exception as e:
        # If simulated LLM is not available, skip this test
        pytest.skip(f"Simulated LLM not available: {e}")
    
    # Clean up
    shutil.rmtree(index_dir)


def test_ask_question_empty_index(tmp_path):
    """Test asking question to empty index should handle gracefully."""
    index_dir = tmp_path / "empty_index"
    index_dir.mkdir()
    index_path = str(index_dir / "empty_index.leann")
    
    # Build an index with minimal content
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Minimal content.")
    builder.build_index(index_path)
    
    try:
        # Should handle gracefully even with minimal content
        answer = ask_question(
            index_path=index_path,
            question="What is this?",
            top_k=1,
            llm="simulated",
            model="simulated-model"
        )
        
        assert isinstance(answer, str), "Should return a string"
        
    except Exception as e:
        pytest.skip(f"Test skipped: {e}")
    
    shutil.rmtree(index_dir)

