#!/usr/bin/env python3

# /// script
# requires-python = ">=3.11"
# ///

"""
This script detects camelcase variables in a Python code file.
"""

import ast
import sys
import re
from pathlib import Path

def find_camelcase_matches(name: str) -> list[str]:
    camelcase_pattern = r"[a-z][A-Z]"
    return re.findall(camelcase_pattern, name)

def detect_camelcase(tree: ast.Module) -> list[str]:
    ans = set()
    for node in ast.walk(tree):
        to_match = []
        if isinstance(node, ast.Name):
            to_match.append(node.id)
        elif isinstance(node, ast.FunctionDef):
            to_match.append(node.name)
            for arg in node.args.args:
                to_match.append(arg.arg)
        else:
            continue
        for val in to_match:
            if len(find_camelcase_matches(val)) > 0:
                ans.add(val)
    return ans

def replace_camelcase_with_snakecase(tree: ast.Module) -> ast.Module:
    for node in ast.walk(tree):
        to_match = {}
        if isinstance(node, ast.Name):
            to_match[node.id] = node
        elif isinstance(node, ast.FunctionDef):
            to_match[node.name] = node
            for arg in node.args.args:
                to_match[arg.arg] = arg
        else:
            continue
        for key, val in to_match.items():
            matches = find_camelcase_matches(key)
            replacement = key
            for match in matches:
                replacement = re.sub(match, f"{match[0]}_{match[1].lower()}", replacement)
            if isinstance(val, ast.Name):
                val.id = replacement           
            elif isinstance(val, ast.FunctionDef):
                val.name = replacement
            elif isinstance(val, ast.arg):
                val.arg = replacement
    return tree

def main(args: list[str]) -> None:
    if len(args) <= 1:
        print("Usage: python3 detect_camelcase.py <PATH TO SOURCE FILE>")
        return
    file_path = Path(args[1])
    assert file_path.exists, "Path supplied does not exist."

    with open(file_path, "r") as f:
        tree = ast.parse(f.read())
    
    if len(args) > 2 and "-r" in args[1:]:
        tree = replace_camelcase_with_snakecase(tree)
        with open(file_path.with_stem(f"{file_path.stem}_snakecase"), "w") as f:
            f.write(ast.unparse(tree))
        return

    ans = detect_camelcase(tree)
    for line in ans:
        print(line)

if __name__=="__main__":
    main(sys.argv)

