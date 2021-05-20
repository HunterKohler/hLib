#!/usr/bin/env python3
# Copyright 2020-2021 John Hunter Kohler. All rights reserved.

import os
import re
import sys

from typing import Callable, Match, Optional, Pattern

Formatter = Callable[[str], str]

COPYRIGHT = "Copyright 2020-2021 John Hunter Kohler. All rights reserved.\n"

SHEBANG_PATTERN = re.compile(r"#!/")


class CommentCategory:
    def __init__(self, patterns: list[str],
                 format: Formatter = None):
        self._format = format
        self.pattern = re.compile(
            r'(\./)?[^.].*\.' + f"({'|'.join(patterns)})")

    def __str__(self):
        return str(self.pattern)

    def match(self, filepath: str):
        return self.pattern.match(filepath)

    def format(self, s: str):
        return self._format(s) if self._format else s


def insert_copyright(filepath: str, category: CommentCategory):
    copyright = category.format(COPYRIGHT)
    lines: list[str] = open(filepath).readlines()
    if not copyright in "\n".join(lines[:10]):  # if not in first 10 lines
        if len(lines) == 0:
            lines = [""]
        match: Optional[Match] = SHEBANG_PATTERN.match(lines[0])
        lines.insert((1 if match else 0), category.format(COPYRIGHT))
        open(filepath, "w").writelines(lines)


HASH_COMMENT = CommentCategory([
    r"py3?",
    r"sh|bash|zsh",
], lambda s: f"# {s}")

LINE_COMMENT = CommentCategory([
    r"c(xx|pp|c)?",
    r"h(xx|pp|h)?",
    r"(j|t)sx?",
    r"java"
], lambda s: f"// {s}")

ARROW_COMMENT = CommentCategory([
    r"html",
    r"hbs|handlebars",
    r"mdx?|markdown",
    r"php"
], lambda s: f"<!-- {s} -->")


PERCENT_COMMENT = CommentCategory([
    "tex"
], lambda s: f"% {s}")

OTHER_COMMENT = CommentCategory(["rst"])

CATEGORIES = [
    HASH_COMMENT,
    LINE_COMMENT,
    ARROW_COMMENT,
    PERCENT_COMMENT,
    OTHER_COMMENT
]


def match_category(s: str) -> Optional[CommentCategory]:
    category: CommentCategory
    for category in CATEGORIES:
        if category.match(s):
            return category
    return None


added = []
other = []
errors = []

dir: str
fnames: list[str]
for dir, _, fnames in os.walk("."):
    fname: str
    for fname in fnames:
        filepath = os.path.join(dir, fname)
        category = match_category(os.path.join(dir, fname))
        if category is OTHER_COMMENT:
            other.append(filepath)
        elif category is not None:
            try:
                insert_copyright(filepath, category)
            except Exception as error:
                errors.append((filepath, error))
            added.append(filepath)

if len(added) > 0:
    print("Added copyright statement to:")
    for filepath in added:
        print("    " + filepath)

if len(other) > 0:
    print("Cannot automatically add copyright statement to:")
    for filepath in other:
        print("    " + filepath)

if len(errors) > 0:
    print("Errors occured writing to some files:")
    filename: str
    for filename, err in errors:
        print(f"\t{filename} {err}")
    sys.exit(1)
