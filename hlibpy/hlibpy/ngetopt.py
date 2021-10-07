from __future__ import annotations

import string

def getopt(args: list[str], shortopts: str, longopts: list[str] = []):
    has_arg: dict[str, bool] = dict()

    for i in range(len(shortopts)):
        has_arg["-" + shortopts[i]] = shortopts.startswith(":", i + 1)
    for opt in longopts:
        arg = opt.endswith("=")
        opt = "--" + (opt[:-1] if arg else opt)
        has_arg[opt] = arg

    # opts: list[tuple[str, str | None]] = []
    # vals: list[str]
    opts = []
    vals = []

    for arg in args:
        if arg.startswith("--"):
            if arg in has_arg:
                arg[]
            else:
                raise Exception(f"Unknown option: {}")
        elif arg.startswith("-"):

    return opts, vals