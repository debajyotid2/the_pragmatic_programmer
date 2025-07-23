#!/usr/bin/env python3

# /// script
# requires-python = ">=3.11"
# dependencies = [
#   "pyyaml",
# ]
# ///

"""
This script converts YAML files to JSON.
"""

import json
import sys
from pathlib import Path
import yaml


def main(args: list[str]) -> None:
    if not len(args) > 1:
        print("Usage: python3 yaml_to_json.py <PATH TO YAML FILE>")
        return
    yaml_path = Path(args[1])
    assert yaml_path.exists(), "Specified path does not exist."
    with open(yaml_path, "r") as f:
        contents = yaml.safe_load(f)
    with open(yaml_path.with_suffix(".json"), "w") as f:
        json.dump(contents, f)

if __name__ == "__main__":
    main(sys.argv)
