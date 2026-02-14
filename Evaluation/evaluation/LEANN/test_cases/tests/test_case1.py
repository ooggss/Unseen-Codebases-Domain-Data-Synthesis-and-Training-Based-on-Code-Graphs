# new_test_case_file

from leann.cli import LeannCLI
from case1 import parse_cli_ask_with_positional_query


def test_cli_ask_accepts_positional_query(tmp_path, monkeypatch):
    monkeypatch.chdir(tmp_path)

    args_list = ["ask", "my-docs", "Where are prompts configured?"]
    
    args = parse_cli_ask_with_positional_query(args_list)

    assert args.command == "ask"
    assert args.index_name == "my-docs"
    assert args.query == "Where are prompts configured?"

