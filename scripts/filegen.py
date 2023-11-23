# =====================================================================================
# File name: filegen.py
#
# Purpose: Script used for generation of source and header files populated with
#          common boilerplate code and block comments.
# =====================================================================================


# =====================================================================================
# Import statements.
# =====================================================================================
import argparse
from pathlib import Path
import subprocess as subproc
import sys


# =====================================================================================
# Main program entry-point.
# =====================================================================================
def main() -> None:
    # Get path to directory of running script. Use this to derive relative paths.
    paths = {"root": Path(__file__).parent, "build": None, "src": None, "inc": None}
    for required_dir in ["build", "src", "inc"]:
        paths[required_dir] = Path(__file__).parent / ".." / required_dir

    # Validate paths.
    if not validate_paths(paths):
        print("Invalid project structure")
        print("Make sure directories src, inc, build are present in project root")
        sys.exit(-1)

    # Find source and header files.
    src_result = subproc.run(
        ["ls", f"{paths['src']}"], stdout=subproc.PIPE, text=True, check=False
    )
    inc_result = subproc.run(
        ["ls", f"{paths['inc']}"], stdout=subproc.PIPE, text=True, check=False
    )
    src_files = [f for f in src_result.stdout.split("\n") if f.endswith(".c")]
    inc_files = [f for f in inc_result.stdout.split("\n") if f.endswith(".h")]


# =====================================================================================
# validate_paths:
# =====================================================================================
def validate_paths(paths: dict) -> bool:
    validated = True
    for key, value in paths.items():
        if value is None:
            print(f"Directory '{key}' not found")
            validated = False
    return validated


# Protection from script from being run during import.
if __name__ == "__main__":
    main()
