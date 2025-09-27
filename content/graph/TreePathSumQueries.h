/**
 * Author: Andi Qu
 * Date: 2020-01-01
 * License: CC0
 * Source: https://codeforces.com/blog/entry/78564
 * Description:
 * Flatten the tree using a preorder traversal.
 * Let the time we enter node $u$ be $\mathit{tin}_u$ and the time we exit it be $\mathit{tout}_u$.
 * Let $A$ be an array/Fenwick tree of size $2N$.
 * To increase the value on a node $u$ by X, increase $A[\mathit{tin}_u]$ by $X$ and decrease $A[\mathit{tout}_u]$ by $X$.
 * To query the sum of the path from the root to $u$, get the sum of the range $[0, \mathit{tin}_u]$.
 * Use LCA and inclusion/exclusion to query paths over $u$ and $v$.
 * Time: O(\log N)
 * Status: tested
 */