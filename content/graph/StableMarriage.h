/**
 * Author: Tyilo
 * Date: 2019-10-07
 * License: CC0
 * Description: Stable marriage, with \texttt{A} and \texttt{B}
 * being $N \times N$ matrices and \texttt{A[a]} being the ordered list of B's
 * according to \texttt{a}'s preference and similarly for \texttt{B[b]}.
 * \text{b} and \texttt{B\_to\_A[b]} are matched up.
 * $O(N^2)$
 * Status: Tested on SPOJ STABLEMP
 */
bool prefers(const vi & prefs, int a1, int a2) {
  trav(a, prefs) {
    if (a == a1) return true;
    if (a == a2) return false;
  }
  return false;
}

vi stable_marriage(const vector<vi> & A, const vector<vi> & B) {
  int N = sz(A);
  queue<int> unmatched;
  vi B_to_A(N, -1);
  rep(a, 0, N) unmatched.push(a);
  while (!unmatched.empty()) {
    int a = unmatched.front();
    unmatched.pop();
    trav(b, A[a]) {
      int a2 = B_to_A[b];
      if (a2 == -1) {
        B_to_A[b] = a;
        break;
      }
      if (prefers(B[b], a, a2)) {
        unmatched.push(a2);
        B_to_A[b] = a;
        break;
      }
    }
  }
  return B_to_A;
}

bool is_stable(const vector<vi> & A, const vector<vi> & B, const vi & B_to_A) {
  int N = sz(A);
  rep(b, 0, N) {
    int a = B_to_A[b];
    trav(b2, A[a]) {
      if (b2 == b) break;
      if (prefers(A[a], b2, b) && prefers(B[b2], a, B_to_A[b2]))
        return false;
    }
  }
  return true;
}
