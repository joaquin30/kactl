#include "../utilities/template.h"
#include "../utilities/random.h"
#include "../utilities/bench.h"
#include "../../content/geometry/Point.h"

#include "../../content/graph/TSP.h"

using vd = vector<double>;
using P = Point<ll>;
vector<vd> make_cost(const vector<P>& ps) {
    int N = sz(ps); vector<vd> C(N, vd(N));
    rep(i, 0, N) rep(j, i+1, N) C[i][j] = C[j][i] = (ps[i] - ps[j]).dist();
    return C;
}

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

using vl = vector<ll>;
vector<vl> matrix(int N) {
    vector<vl> cost(N, vl(N));
    rep(i, 0, N) rep(j, i + 1, N) cost[i][j] = cost[j][i] = randRange((int64_t)INF);
    return cost;
}

void test_correctness(int iters) {
    rep(_, 0, iters) {
        int N = randIncl(2, 10);
        // generate symmetric distance matrix
        auto cost = matrix(N);
        assert(TSP(cost) == perm(cost));
    }

    int64_t lim = 1 << 20;
    rep(_, 0, iters) {
        int N = randIncl(2, 10);
        vector<P> ps(N);
        trav(p, ps) p.x = randIncl(-lim, lim), p.y = randIncl(-lim, lim);
        auto cost = make_cost(ps);
        assert(fabs(TSP(cost) - perm(cost)) < 1e-7);
    }
}

void test_time() {
    rep(N, 14, 23) {
        auto cost = matrix(N);
        ll t1, t2;
        {
            timeit t("TSP: N = " + to_string(N));
            t1 = TSP(cost);
        }
        {
            timeit t("NDP: N = " + to_string(N));
            t2 = naiveDP(cost);
        }
        assert(t1 == t2);
    }
}

signed main() {
    test_correctness(1000);
    test_time();
    cout << "Tests passed!" << endl;
}
