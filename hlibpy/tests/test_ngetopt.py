from __future__ import annotations

import pytest

from hlibpy import ngetopt

import getopt

getopt.getopt


def test_getopt_errors():
    with pytest.raises(TypeError, match="Duplicate opt: '-a'"):
        ngetopt.getopt([], "aba")
    with pytest.raises(TypeError, match="Invalid opt: '- '"):
        ngetopt.getopt([], "a b")
    with pytest.raises(TypeError, match="Invalid opt: '-:'"):
        ngetopt.getopt([], ":")
    with pytest.raises(TypeError, match="Invalid opt: '-:'"):
        ngetopt.getopt([], "a::")
    with pytest.raises(TypeError, match="Duplicate opt: '--a'"):
        ngetopt.getopt([], None, ["a", "b", "a"])
    with pytest.raises(TypeError, match="Invalid opt: '--'"):
        ngetopt.getopt([], None, [""])
    with pytest.raises(TypeError, match="Invalid opt: '--'"):
        ngetopt.getopt([], None, ["="])
    with pytest.raises(TypeError, match="Invalid opt: '-- '"):
        ngetopt.getopt([], None, [" "])
    with pytest.raises(TypeError, match="Invalid opt: '-- '"):
        ngetopt.getopt([], None, [" ="])
    with pytest.raises(ngetopt.UnknownOptError, match="Unknown option: '-a'"):
        ngetopt.getopt(["-a"], None, ["a"])
    with pytest.raises(ngetopt.UnknownOptError, match="Unknown option: '--a'"):
        ngetopt.getopt(["--a"], "a")
    with pytest.raises(ngetopt.MissingArgError, match="Missing option argument: '-a'"):
        ngetopt.getopt(["-a"], "a:")
    with pytest.raises(ngetopt.MissingArgError, match="Missing option argument: '--a'"):
        ngetopt.getopt(["--a"], None, ["a="])

    assert ngetopt.getopt([], None) == [], []
