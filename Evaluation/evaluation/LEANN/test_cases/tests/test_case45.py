# new_test_case_file

import pytest
from pathlib import Path
from case45 import export_index_metadata, import_index_from_metadata
from leann.api import LeannBuilder, LeannSearcher
import shutil


def test_export_index_metadata_and_import(tmp_path):
    """Test exporting index metadata and importing to rebuild index."""
    # Build original index
    original_index = str(tmp_path / "original.leann")
    builder = LeannBuilder(backend_name="hnsw")
    builder.add_text("Python tutorial", metadata={"category": "tech", "rating": 5})
    builder.add_text("JavaScript guide", metadata={"category": "web", "rating": 4})
    builder.build_index(original_index)
    
    # Export metadata
    export_file = str(tmp_path / "export.json")
    export_result = export_index_metadata(original_index, export_file)
    
    assert export_result["status"] == "success", "Export should succeed"
    assert export_result["exported_passages"] > 0, "Should export passages"
    assert Path(export_file).exists(), "Export file should exist"
    
    # Import and rebuild
    new_index = str(tmp_path / "imported.leann")
    import_result = import_index_from_metadata(export_file, new_index)
    
    assert import_result["status"] == "success", "Import should succeed"
    assert import_result["passages_imported"] == export_result["exported_passages"], \
        "Should import same number of passages"
    
    # Verify new index is searchable
    searcher = LeannSearcher(index_path=new_index)
    results = searcher.search("Python", top_k=5)
    assert len(results) > 0, "Imported index should be searchable"


def test_export_index_metadata_nonexistent():
    """Test exporting non-existent index should raise FileNotFoundError."""
    with pytest.raises(FileNotFoundError):
        export_index_metadata("/nonexistent/index.leann", "/tmp/export.json")
