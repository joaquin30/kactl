/**
 * Author: Tyilo
 * Date: 2019-10-07
 * License: CC0
 * Description: Stable marriage, with \texttt{A} and \texttt{B}
 * being $N \times N$ matrices and \texttt{A[a]} being the ordered list of B's
 * according to \texttt{a}'s preference and similarly for \texttt{B[b]}.
 * \text{b} and \texttt{B\_to\_A[b]} are matched up.
 * Time: $O(N^2)$
 * Status: Tested on SPOJ STABLEMP
 */
using vvi = vector<vi>;
vvi prefer_rank(const vvi& B) {
  int N = sz(B); vvi res(N, vi(N));
  rep(b, 0, N) rep(i, 0, N) res[b][B[b][i]] = i;
  return res;
}
vi stable_marriage(const vvi& A, const vvi& B) {
  int N = sz(A);
  queue<int> unmatched;
  vi B_to_A(N, -1);
  auto prefer_B = prefer_rank(B);
  rep(a, 0, N) unmatched.push(a);
  while (!unmatched.empty()) {
    int a = unmatched.front();
    unmatched.pop();
    for(int b : A[a]) {
      int a2 = B_to_A[b];
      if (a2 == -1) {
        B_to_A[b] = a;
        break;
      }
      if (prefer_B[b][a] < prefer_B[b][a2]) {
        unmatched.push(a2);
        B_to_A[b] = a;
        break;
      }
    }
  }
  return B_to_A;
}
bool is_stable(const vvi& A, const vvi& B, const vi& B_to_A) {
  int N = sz(A);
  auto prefer_A = prefer_rank(A);
  auto prefer_B = prefer_rank(B);
  rep(b, 0, N) {
    int a = B_to_A[b];
    for(int b2 : A[a]) {
      if (b2 == b) break;
      if (prefer_A[a][b2] < prefer_A[a][b] &&
          prefer_B[b2][a] < prefer_B[b2][B_to_A[b2]])
        return false;
    }
  }
  return true;
}
