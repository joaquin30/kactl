/**
 * Author: Oskar Haarklou Veileborg
 * Date: 2020-04-14
 * License: CC0
 * Description: Given a symmetric distance matrix, computes the min. length of
 * a tour beginning and ending at node N visiting all other nodes exactly once.
 * Time: O(2^n n^2). For n=22 $\approx 0.5s$.
 * Status: Stress-tested and tested on Kattis: toursdesalesforce
 */
#pragma once

const int MAXN = 21; // 1 less than actual MAXN is fine
using T = long long; // can also use double
const T INF = 1e12;
#define repbits(x, bs) for(int x, y = bs; \
  y && ((x = __builtin_ctz(y)) || y); y ^= y&-y)
T DP[1 << MAXN][MAXN];
T TSP(const vector<vector<T>>& C) {
  int N = sz(C)-1, M = 1 << N;
  memset(&DP, 0, sizeof(DP));
  rep(i, 0, N) DP[1 << i][i] += DP[M-1][i] = C[i][N];
  rep(bs, 3, M) if(bs ^ (bs&-bs)) repbits(j, bs) {
    int nbs = bs ^ (1 << j); T r = INF;
    repbits(i, nbs) r = min(r, DP[nbs][i] + C[i][j]);
    DP[bs][j] += r;
  }
  T best = INF; rep(i, 0, N) best = min(best, DP[M-1][i]);
  return best;
}
