/**
 * Author: Oskar Haarklou Veileborg
 * Date: 2020-04-14
 * License: CC0
 * Description: Given a symmetric distance matrix, computes the minimum length of
 * a cycle that visits every node exactly once.
 * Time: O(2^n n^2). For n=22 $\approx 0.5s$.
 * Status: Stress-tested and tested on Kattis: toursdesalesforce
 */
#pragma once

const int MAXN = 21; // 1 less than actual MAXN is fine
using T = ll; // can also use double
const T INF = 1e12;
#define repbits(bs, x) \
  for(int y = bs, x; x = __builtin_ctz(y), y; y ^= y&-y)
T DP[1 << MAXN][MAXN];
T TSP(const vector<vector<T>>& C) {
  int N = sz(C)-1, M = 1 << N;
  rep(bs, 1, M) rep(i, 0, N) DP[bs][i] = INF;
  rep(i, 0, N) DP[1 << i][i] = C[i][N];
  rep(bs, 1, M) repbits(bs, j) {
    int nbs = bs ^ (1 << j);
    repbits(nbs, i)
      DP[bs][j] = min(DP[bs][j], DP[nbs][i] + C[i][j]);
  }
  T best = INF;
  rep(i, 0, N) best = min(best, DP[M-1][i] + C[i][N]);
  return best;
}
