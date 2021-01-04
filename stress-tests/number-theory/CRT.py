#!/usr/bin/env python3.9
from math import lcm
from pathlib import Path

import hypothesis.strategies as st
from hypothesis import given, settings

kactl_path, crt_path = __file__.rsplit("stress-tests/", 1)

with (Path(kactl_path) / "content" / crt_path).open() as f:
    exec(f.read())


@st.composite
def crt_input(draw):
    mod = draw(st.lists(st.integers(min_value=1)))
    N = lcm(*mod)
    x = draw(st.integers(min_value=0, max_value=N - 1))
    rem = [x % m for m in mod]
    return (rem, mod, x)


@settings(max_examples=10**4)
@given(crt_input())
def test_crt(args):
    rem, mod, x = args

    x2 = crt(rem, mod)
    assert x == x2
