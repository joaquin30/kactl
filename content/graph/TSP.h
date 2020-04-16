/**
 * Author: Oskar Haarklou Veileborg
 * Date: 2020-04-14
 * License: CC0
 * Description: Given a symmetric distance matrix, computes the minimum length of a cycle that visits every node.
 * Time: O(2^n n^2). For n=21 $\approx 0.5s$. Runs 40\% faster if DP array is global.
 * Status: Stress-tested and tested on Kattis: toursdesalesforce
 */
#pragma once

const double INF = 1e12;
#define repbits(bs, x) for(int y = (bs), x; x = __builtin_ctz(y)+1, y; y ^= y&-y)
#define vt vector<T>
template<class T> T TSP(const vector<vt>& C) {
    int N = sz(C), M = 1 << (N-1);
    vector<vt> DP(M, vt(N, INF));
    rep(bs, 1, M) repbits(bs, j) {
        int nbs = bs ^ (1 << (j-1));
        if(!nbs) DP[bs][j] = C[0][j];
        else repbits(nbs, i)
            DP[bs][j] = min(DP[bs][j], DP[nbs][i] + C[i][j]);
    }
    T best = INF;
    rep(i, 1, N) best = min(best, DP[M-1][i] + C[i][0]);
    return best;
}
