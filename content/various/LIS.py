'''
 * Author: Asger Hautop Drewsen
 * License: CC0
 * Description: Compute indices for the longest increasing subsequence.
 * Status: Tested on Kattis, longincsubseq
 * Time: $O(N \log N)$
'''
from bisect import bisect_left

def lis(S):
	prev, res = [], []
	for i, v in enumerate(S):
		el = (v, i)
		# v + 1 for non-decreasing
		j = bisect_left(res, (v, 0))
		if j == len(res):
			res.append(el)
		else:
			res[j] = el
		prev.append(0 if j == 0 else res[j - 1][1])
	ans = []
	cur = res[-1][1]
	for _ in range(len(res)):
		ans.append(cur)
		cur = prev[cur]
	return ans[::-1]
