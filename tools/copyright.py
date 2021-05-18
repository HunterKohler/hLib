# Copyright 2020-2021 John Hunter Kohler. All rights reserved.

import os
import re
from typing import Callable, Optional, Pattern

Formatter = Callable[[str], str]

COPYRIGHT = "Copyright 2020-2021 John Hunter Kohler. All rights reserved."

class CommentCategory:
    pattern: Pattern
    format: Formatter

    def __init__(self, patterns: list[str],
                       format: Optional[Formatter] = None):
        self.pattern = re.compile(r'(\./)?[^.].*\.' + f"({'|'.join(patterns)})")
        self.format = format

    def __str__(self):
        return self.pattern

    def match(self, filepath: str):
        return self.pattern.match(filepath)


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

OTHER_COMMENT = CommentCategory([
        "rst"
    ])

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
            return s

added = []
other = []

dir: str
fnames: list[str]
for dir, _, fnames in os.walk("."):
    fname: str
    for fname in fnames:
        filepath: str = os.path.join(dir, fname)
        category: CommentCategory = match_category(os.path.join(dir, fname))
        if category is OTHER_COMMENT:
            other.append(filepath)
        elif category is not None:
            added.append(filepath)

if len(added) > 0:
    print("Added copyright statement to:")
    for filepath in added:
        print("    " + filepath)

if len(other) > 0:
    print("Could not add copyright statement to:")
    for filepath in other:
        print("    " + filepath)



