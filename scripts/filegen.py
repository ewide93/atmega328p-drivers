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
import os
import sys
from pathlib import Path
from enum import IntEnum


# =====================================================================================
# Main program entry-point.
# =====================================================================================
def main() -> None:
    # Enumerations.
    class ProgramState(IntEnum):
        SETUP = 0
        GEN_ALL = 1
        GEN_HEADER = 2
        GEN_SOURCE = 3

    # Variables
    state = ProgramState.SETUP

    # Verify project layout.
    paths = {"scripts": Path(__file__).parent, "build": None, "src": None, "inc": None}
    for required_dir in ["build", "src", "inc"]:
        temp = Path(__file__).parent / ".." / required_dir
        if temp.exists() and temp.is_dir():
            paths[required_dir] = Path(__file__).parent / ".." / required_dir
        else:
            print(f"Directory {required_dir} not found.")
            sys.exit(-1)

    # Set up parser for command line arguments.
    parser = argparse.ArgumentParser(
        usage="%(prog)s <file_name> <option>",
        description="Generate source and/or header files with boilerplate code.",
    )
    parser.add_argument(
        "file_name",
        help="Name of generated file/files. Should be given without extension.",
    )
    parser.add_argument(
        "-l",
        "--length",
        help="Maximum length of columns, defaults to 100.",
        default=100,
        type=int,
    )
    exclusive_args = parser.add_mutually_exclusive_group()
    exclusive_args.add_argument(
        "-s",
        "--source",
        help="Flag signalling that only a source file should be generated.",
        action="store_true",
    )
    exclusive_args.add_argument(
        "-i",
        "--header",
        help="Flag signalling that only a header file should be generated.",
        action="store_true",
    )

    # Parse command line arguments.
    args = parser.parse_args()
    file_name = args.file_name
    source_flag = args.source
    header_flag = args.header
    line_length = args.length

    # Determine what files are to be generated.
    if source_flag:
        state = ProgramState.GEN_SOURCE
    elif header_flag:
        state = ProgramState.GEN_HEADER
    else:
        state = ProgramState.GEN_ALL

    # Verify that files won't be overwritten, then generate files.
    if state == ProgramState.GEN_ALL or state == ProgramState.GEN_SOURCE:
        src_files = [f for f in os.listdir(paths["src"]) if f.endswith(".c")]
        new_src_file = f"{file_name}.c"
        if new_src_file in src_files:
            print(f"{new_src_file} already exists.")
            sys.exit(-1)
        else:
            generate_source_file(new_src_file, paths["src"], line_length)
    if state == ProgramState.GEN_ALL or state == ProgramState.GEN_HEADER:
        inc_files = [f for f in os.listdir(paths["inc"]) if f.endswith(".h")]
        new_inc_file = f"{file_name}.h"
        if new_inc_file in inc_files:
            print(f"{new_inc_file} already exists.")
            sys.exit(-1)
        else:
            generate_header_file(new_inc_file, paths["inc"], line_length)

    # Exit program.
    sys.exit(0)


# =====================================================================================
# block_comment:
# =====================================================================================
def block_comment(line_length: int, label: str) -> str:
    separator = f"//{'=' * (line_length - 2)}\n"
    text = f"// {label}\n"
    return f"{separator}{text}{separator}\n\n"


# =====================================================================================
# header_guard_start:
# =====================================================================================
def header_guard_start(file_name: str) -> str:
    name, extension = file_name.upper().split(".")
    mangled_name = f"_{name}_{extension}_"
    return f"#ifndef {mangled_name}\n#define {mangled_name}\n"


# =====================================================================================
# header_guard_end:
# =====================================================================================
def header_guard_end(file_name: str) -> str:
    name, extension = file_name.upper().split(".")
    mangled_name = f"_{name}_{extension}_"
    return f"#endif // {mangled_name}"


# =====================================================================================
# file_header:
# =====================================================================================
def file_header(line_length: int, name: str, header_file: bool = False) -> str:
    separator = f"//{'=' * (line_length - 2)}\n"
    text = f"//\n// File name: {name}\n//\n// Purpose: \n//\n"
    if header_file:
        return f"{separator}{text}{separator}{header_guard_start(name)}\n\n"
    else:
        return f"{separator}{text}{separator}\n\n"


# =====================================================================================
# generate_source_file:
# =====================================================================================
def generate_source_file(file_name: str, path: Path | None, line_length: int) -> None:
    if path is None:
        print(f"Error during generation of {file_name}")
        sys.exit(-1)
    with open(path / file_name, "w") as f:
        f.write(file_header(line_length, file_name))
        f.write(block_comment(line_length, "Include directives"))
        f.write(block_comment(line_length, "Local preprocessor definitions"))
        f.write(block_comment(line_length, "Local preprocessor definitions"))
        f.write(block_comment(line_length, "Local variables"))
        f.write(block_comment(line_length, "Local function prototypes"))
        f.write(block_comment(line_length, "External variable definitions"))
        f.write(block_comment(line_length, "Local function definitions"))
        f.write(block_comment(line_length, "External function definitions"))
        print(f"Generated file: {file_name}")


# =====================================================================================
# generate_header_file:
# =====================================================================================
def generate_header_file(file_name: str, path: Path | None, line_length: int) -> None:
    if path is None:
        print(f"Error during generation of {file_name}")
        sys.exit(-1)
    with open(path / file_name, "w") as f:
        f.write(file_header(line_length, file_name, header_file=True))
        f.write(block_comment(line_length, "Include directives"))
        f.write(block_comment(line_length, "Preprocessor definitions"))
        f.write(block_comment(line_length, "Structures and enumerations"))
        f.write(block_comment(line_length, "External variable declarations"))
        f.write(block_comment(line_length, "Function prototypes"))
        f.write(header_guard_end(file_name))
        print(f"Generated file: {file_name}")


# Protection from script being run during import.
if __name__ == "__main__":
    main()
