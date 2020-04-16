/**
 * Author: Oskar Haarklou Veileborg
 * Date: 2020-04-14
 * License: CC0
 * Description: Given a symmetric distance matrix, computes the minimum length of
 * a cycle that visits every node.
 * Time: O(2^n n^2). For n=21 $\approx 0.5s$. Runs 40\% faster if DP array is global.
 * Status: Stress-tested and tested on Kattis: toursdesalesforce
 */
#pragma once

const double INF = 1e12;
#define repbits(bs, x) for(int y = bs, x; \
  x = __builtin_ctz(y), y; y ^= y&-y)
#define vt vector<T>
template<class T> T TSP(const vector<vt>& C) {
  int N = sz(C)-1, M = 1 << N;
  vector<vt> DP(M, vt(N, INF));
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
