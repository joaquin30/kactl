/**
 * Author: Oskar Haarklou Veileborg
 * Date: 2020-04-14
 * License: CC0
 * Description: Given a distance matrix, computes for all $i < S = N - 1$,
 * the min.\ length of all paths visiting all nodes starting at $S$ and ending at $i$.
 * To compute the cyclic TSP-tour length use $\min \{ \mathrm{res}[i] + C[i][S] \mid i < S \}$.
 * Time: O(2^N N^2). $N = 22 \approx 0.5 s$.
 * Status: Stress-tested and tested on Kattis: toursdesalesforce, supermario169
 */
#pragma once

const int MAXS = 21; // 1 less than MAXN
using T = ll; // can also use double
const T INF = 1e12;
#define repbits(x, bs) for(int x, y = bs; \
  y && ((x = __builtin_ctz(y)) || y); y ^= y&-y)
T DP[1 << MAXS][MAXS];
T * TSP(const vector<vector<T>>& C) {
  int S = sz(C)-1, M = 1 << S;
  rep(i, 0, S) DP[1 << i][i] = C[S][i];
  rep(bs, 3, M) if(__builtin_popcount(bs) > 1) repbits(j, bs) {
    int nbs = bs ^ (1 << j); T& r = DP[bs][j] = INF;
    repbits(i, nbs) r = min(r, DP[nbs][i] + C[i][j]);
  }
  return DP[M-1];
}
