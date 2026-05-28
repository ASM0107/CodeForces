# Approach Patterns

Recurring observations and techniques distilled from contest experience.

---

## 1. Prefix/Suffix Decomposition

**Pattern:** When a problem asks for an optimal split point, partition, or dividing line, precompute prefix and suffix aggregates (min, max, sum, count) and sweep the split point in O(n).

**Why it works:** Many optimization problems over arrays decompose into "best of left" + "best of right" at each position. Prefix/suffix arrays make each query O(1).

**Seen in:** R1098-D (prefix/suffix min-max), Edu-B (prefix counts + sweep), R1099-B (gap analysis between inversions), R1100-C2 (running diff).

---

## 2. Backward Greedy

**Pattern:** When operations affect prefixes or have cascading left-to-right effects, process the array right-to-left. Each decision becomes locally optimal because downstream effects are already resolved.

**Why it works:** Forward processing creates dependencies (choosing an operation at position i affects positions 0..i). Backward processing breaks these dependencies — each position only affects already-decided positions.

**Seen in:** R1100-C1 (prefix negation → backward sweep with parity).

---

## 3. Binary Search on Answer

**Pattern:** When the answer is monotone (if x works, then x−1 also works), binary search on the answer value and reduce to a feasibility check.

**Key requirement:** The check function must be monotone in the candidate answer. Prove this before implementing.

**Seen in:** R1100-D (median ≥ x is monotone in x), Edu-E (custom binary search on decreasing cost array).

---

## 4. Exchange Argument for Greedy Proofs

**Pattern:** To prove a greedy choice is optimal, assume a solution that doesn't make that choice and show you can "exchange" it for the greedy choice without worsening the objective.

**Seen in:** R1100-B (always taking max(aᵢ, bᵢ) — swapping in the max can only improve).

---

## 5. Monotone Envelope Reduction

**Pattern:** When dealing with 2D points where you want a min/max of f(x, y), filter to the Pareto frontier first. If the problem has anti-correlated structure (x increases → y decreases), the frontier is small and structured.

**Why it works:** Dominated points can never be optimal. The filtered set has monotone structure that enables binary search or sparse table queries.

**Seen in:** Edu-E (sorted by position, filtered to decreasing cost → sparse table on sum).

---

## 6. Convergence Path Enumeration

**Pattern:** When elements transform via deterministic rules (e.g., Collatz-like), trace each element's path and find the cheapest common meeting point across all paths.

**Why it works:** Deterministic rules mean each element visits O(log n) values. Total work is bounded.

**Seen in:** R1099-C (odd→+1, even→/2 paths converge; hash map tracks costs).

---

## 7. Tree DP with Knapsack Merge

**Pattern:** On trees, DP states at a node are computed by sequentially merging children via convolution. The total work is bounded by O(n·k) due to the subtree-size argument.

**Key insight:** Don't merge all children simultaneously — merge them one at a time into a running accumulator. This keeps the per-merge work proportional to the product of current size and child size, which telescopes.

**Seen in:** R1099-E (4-state DP merged via knapsack, iterative BFS traversal).

---

## 8. Region Decomposition for 2D Queries

**Pattern:** When a query constrains two independent dimensions, the index space decomposes into a grid of regions. In each region, one or both dimensions are bounded by constants, simplifying the query.

**Seen in:** Edu-E (3×3 grid from position and cost bounds; each cell reduces to a constant or a 1D range query).

---

## 9. Digit-by-Digit Construction

**Pattern:** To find the nearest number satisfying digit constraints, build it greedily from the most significant digit. When forced to diverge from the target, fill remaining positions with the extreme digit (max for ≤, min for ≥). Backtrack when no valid digit exists.

**Why it works:** The most significant digit dominates the value. Greedy + backtracking explores at most O(L²) combinations for L-digit numbers.

**Seen in:** R1098-C1/C2 (`find_leq` and `find_geq` with backtracking).

---

## General Heuristics

- **When stuck on implementation:** simplify the state. Can a 2D state become 1D? Can you precompute one dimension?
- **When the greedy seems wrong:** look for a counterexample with n=3 or n=4. If you can't find one, try proving via exchange argument.
- **When complexity is borderline:** estimate the constant factor. Hash maps have ~10x overhead vs arrays. Sparse tables have better constants than segment trees for static queries.
- **For constructive problems:** work backward from the answer. What must the last element be? The second-to-last?
