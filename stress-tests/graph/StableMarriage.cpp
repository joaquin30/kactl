#include "../utilities/template.h"
#include "../utilities/random.h"
#include "../utilities/bench.h"

#include "../../content/graph/StableMarriage.h"

array<vector<vi>, 2> random_input(int N) {
	array<vector<vi>, 2> res = {vector<vi>(N, vi(N)), vector<vi>(N, vi(N))};
	rep(i, 0, 2) {
		rep(j, 0, N) {
			iota(all(res[i][j]), 0);
			random_shuffle(all(res[i][j]));
		}
	}
	return res;
}

// From https://doi.org/10.1137/0219004
// Solution is the identity map
array<vector<vi>, 2> worst_case_input(int N) {
	vector<vi> A(N, vi(N));
	vector<vi> B(N, vi(N));

	rep(i, 0, N) {
		iota(all(A[i]), 0);
	}

	rep(i, 0, N) {
		if (i == 0 || i == N - 1) {
			iota(all(B[i]), 0);
		} else {
			rep(j, 0, N) {
				B[i][j] =
					j < i - 1? j:
					j == i - 1? i:
					j == i? N - 1:
					j == i + 1? i - 1:
					j - 1;
			}
		}
	}

	return {A, B};
}

void test_correctness(int iters) {
	rep(_, 0, iters) {
		int N = randIncl(1, 500);
		auto [A, B] = random_input(N);
		auto B_to_A = stable_marriage(A, B);
		assert(is_stable(A, B, B_to_A));
	}
}

void test_time() {
	int N = 256;
	while (N <= 8192) {
		auto [A, B] = worst_case_input(N);

		vi B_to_A;
		{
			timeit t("N = " + to_string(N));
			B_to_A = stable_marriage(A, B);
		}

		assert(is_stable(A, B, B_to_A));

		vi expected(N);
		iota(all(expected), 0);
		assert(B_to_A == expected);

		N *= 2;
	}
}

int main() {
	test_correctness(100);
	test_time();
	cout << "Tests passed!" << endl;
}
