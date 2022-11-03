#!/usr/bin/env pypy3
import sys
from pathlib import Path
from collections import defaultdict
from time import process_time
import importlib.util

kactl_path, dinics_path = __file__.rsplit("stress-tests/", 1)

spec = importlib.util.spec_from_file_location("dimpl", Path(kactl_path) / "content" / dinics_path)
dimpl = importlib.util.module_from_spec(spec)
spec.loader.exec_module(dimpl)

def test_dinics():
    r"""
    All edges are left to right with cap 1
      x   x           x
     / \ / \         / \
    x-x-x-x-x ..... x-x-x -> x
     \ / \ /         \ /
      x   x           x
    After finding the augmenting path, there are 2^N paths
    that lead to the node before the sink, which we do not
    want to explore!
    """
    DEGREE = 3

    for pw in range(1, 10):
        start = process_time()
        N = 1 << pw
        M = N * (DEGREE+1) + 2
        G = [defaultdict(int) for _ in range(M)]
        for i in range(0, M-2, DEGREE+1):
            for j in range(1, DEGREE+1):
                G[i][i+j] = G[i+j][i+DEGREE+1] = 1

        G[M-2][M-1] = 1
        flow, _ = dimpl.dinics(G, 0, M-1)
        assert flow == 1
        print(f"{N=} {M=} {process_time() - start:.2f}s", file=sys.stderr)

if __name__ == "__main__":
    test_dinics()
    print("Tests passed!")
