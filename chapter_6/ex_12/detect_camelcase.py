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

def detect_camelcase(tree: ast.Module) -> list[str]:
    ans = set()
    camelcase_pattern = r"[a-z][A-Z]"
    for node in ast.walk(tree):
        if isinstance(node, ast.Name):
            matches = re.findall(camelcase_pattern, node.id)
            if len(matches) > 0:
                ans.add(node.id)
    return ans

def replace_camelcase_with_snakecase(tree: ast.Module) -> ast.Module:
    camelcase_pattern = r"[a-z][A-Z]"
    for node in ast.walk(tree):
        if isinstance(node, ast.Name):
            matches = re.findall(camelcase_pattern, node.id)
            for match in matches:
                node.id = re.sub(match, f"{match[0]}_{match[1].lower()}", node.id)
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

