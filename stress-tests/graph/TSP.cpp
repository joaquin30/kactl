#include "../utilities/template.h"
#include "../utilities/random.h"
#include "../utilities/bench.h"
#include "../../content/geometry/Point.h"

#include "../../content/graph/TSP.h"

#define trav(a, b) for(auto& a : b)
// TODO: Make tests with assymetric distance matrices

using vd = vector<double>;
using P = Point<ll>;
vector<vd> make_cost(const vector<P>& ps) {
    int N = sz(ps); vector<vd> C(N, vd(N));
    rep(i, 0, N) rep(j, i+1, N) C[i][j] = C[j][i] = (ps[i] - ps[j]).dist();
    return C;
}

namespace TSPD {
    using T = double; // can also use double
    const T INF = 1e12;
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
}

#define vt vector<T>
template<class T> T naiveDP(const vector<vt>& C) {
    int N = sz(C), M = 1 << N;
    vector<vt> DP(M, vt(N, INF));
    DP[1][0] = 0;
    rep(bs, 3, M) if (bs&1) {
        rep(j, 1, N) if (bs & (1 << j)) {
            int nbs = bs ^ (1 << j);
            rep(i, 0, N) if (i != j && bs & (1 << i)) {
                DP[bs][j] = min(DP[bs][j], DP[nbs][i] + C[i][j]);
            }
        }
    }
    T best = INF;
    rep(i, 1, N) best = min(best, DP[M-1][i] + C[i][0]);
    return best;
}

template<class T> T perm(const vector<vt>& C) {
    T best = INF;
    vi order(sz(C));
    iota(all(order), 0);
    do {
        int prev = order.back();
        T cost = 0;
        rep(i, 0, sz(C)) {
            cost += C[prev][order[i]];
            prev = order[i];
        }
        best = min(best, cost);
    } while(next_permutation(all(order)));
    return best;
}

template<class T> vt perm_path(const vector<vt>& C, int S) {
    assert(S == sz(C) - 1); // for simplicity of implementation
    vi order(sz(C) - 1);
    vt best(sz(C) - 1, INF);
    iota(all(order), 0);
    do {
        int prev = S;
        T cost = 0;
        rep(i, 0, sz(C) - 1) {
            cost += C[prev][order[i]];
            prev = order[i];
        }
        int last = order.back();
        best[last] = min(best[last], cost);
    } while(next_permutation(all(order)));
    return best;
}

template <typename T, typename F>
T min_tour(F tsp_f, const vector<vector<T>> & cost) {
    auto res = tsp_f(cost);
    T best = INF;
    int S = sz(cost) - 1;
    rep(i, 0, S) best = min(best, res[i] + cost[i][S]);
    return best;
}

using vl = vector<ll>;
vector<vl> matrix(int N) {
    vector<vl> cost(N, vl(N));
    rep(i, 0, N) rep(j, 0, N) {
        if (i == j) continue;
        cost[i][j] = randRange((int64_t)INF/N);
    }
    return cost;
}

void test_correctness(int iters) {
    rep(_, 0, iters) {
        int N = randIncl(2, 10);
        // generate asymmetric distance matrix
        auto cost = matrix(N);
        auto c1 = min_tour(TSP, cost), c2 = perm(cost);
        assert(c1 == c2);
    }

    rep(_, 0, iters) {
        int N = randIncl(2, 10);
        auto cost = matrix(N);
        auto r1 = TSP(cost);
        auto r2 = perm_path(cost, N - 1);
        rep(i, 0, N - 1) {
            assert(r1[i] == r2[i]);
        }
    }

    int64_t lim = 1 << 20;
    rep(_, 0, iters) {
        int N = randIncl(2, 10);
        vector<P> ps(N);
        trav(p, ps) p.x = randIncl(-lim, lim), p.y = randIncl(-lim, lim);
        auto cost = make_cost(ps);
        assert(fabs(min_tour(TSPD::TSP, cost) - perm(cost)) < 1e-7);
    }
}

void test_time() {
    rep(N, 14, 23) {
        auto cost = matrix(N);
        ll t1, t2;
        {
            timeit t("TSP: N = " + to_string(N));
            t1 = min_tour(TSP, cost);
        }
        {
            timeit t("NDP: N = " + to_string(N));
            t2 = naiveDP(cost);
        }
        assert(t1 == t2);
    }
}

signed main() {
    test_correctness(200);
    test_time();
    cout << "Tests passed!" << endl;
}
