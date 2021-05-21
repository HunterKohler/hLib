#!/usr/bin/env python3

import glob
import os
import sys
from typing import Callable

result_list = list[tuple[bool, str]]
rule_return_type = tuple[bool, result_list]
rule_type = Callable[[list[str]], rule_return_type]


def main(argv: list[str]) -> None:
    if len(argv) != 1:
        file_paths = find(argv[1:])
    if len(argv) == 1 or len(file_paths) == 0:
        stderr("Error: No files specified.")
        stderr("Usage: ./cpp_ext.py files...")
        sys.exit(1)

    # Running all rules
    rule: rule_type
    for rule in [
        # headers,
        extensions
    ]:
        any_failed, results = rule(file_paths)
        if any_failed:
            for fail, file_path in results:
                if fail:
                    stderr(f"    failed: {file_path}")
                else:
                    stdout(f"    passed: {file_path}")
        else:
            stdout(f"{rule.__name__}: success")


def find(paths: list[str]) -> list[str]:
    print(paths)
    file_paths = []

    # Ensure user supplied paths are real, and expand directories.
    for path in paths:
        if os.path.isdir(path):
            dir_contents = find_in_dir(path)
            if len(dir_contents) == 0:
                stderr(f"Error: No file matches under directory: {path}")
                sys.exit(1)
        elif path.split(".")[-1] not in cpp_extension_set:
            print(path)
            print(path.split(".")[-1])
            print(cpp_extension_set)
            stderr(f"Error: Invalid input file (invalid extension): {path}")
            sys.exit(1)
        elif os.path.isfile(path):
            file_paths.append(path)
        else:
            stderr(f"Error: Could not find file or directory: {path}")
            sys.exit(1)
    return file_paths


cpp_extension_set: set[str] = {
    "cpp", "cxx", "cc", "c++", "hpp", "hxx", "hh", "h"
}


def find_in_dir(dir_path: str, ext: set[str] = cpp_extension_set) -> list[str]:
    file_paths = glob.glob(os.path.join(dir_path, f"**.{','.join(ext)}"))
    return file_paths


# def headers(fule_paths: list[str]) -> rule_return_type:
#     pass


# Check for bad C++ file extensions
def extensions(file_paths: list[str],
               valid_ext: list[str] = ["cpp", "h"]
               ) -> tuple[bool, list[tuple[bool, str]]]:
    print(file_paths)
    valid_ext_set: set[str] = set(valid_ext)
    any_failed: bool = False
    results: result_list = []
    path: str
    for path in file_paths:
        ext: str = path.split(".")[-1]
        failed = ext not in valid_ext_set
        any_failed |= failed
        results.append((failed, path))
    return (any_failed, results)


def stderr(*a, **k) -> None: print(*a, **k, file=sys.stderr)
def stdout(*a, **k) -> None: print(*a, **k, file=sys.stdout)


if __name__ == "__main__":
    main(sys.argv)
