# Spectral Cup 2026 Round 2 / Codeforces Round 1100 (Div. 1 + Div. 2)

**Contest:** [#2229](https://codeforces.com/contest/2229) · **Rank:** 1838 · **Solved:** 5/10 · **Rating:** 1549 → 1658

First Div. 1+2 contest. Solving 5 problems against the combined field pushed rating to Expert.

---

## A — Slimes on a Line

**Key Insight:**
Slimes on a line merge pairwise. Each merge consumes one unit of gap. The maximum number of merges is `⌊(max − min) / 2⌋` — only the span matters, not the internal distribution. Interior positions are irrelevant; only the extremes determine the answer.

**Concepts:** greedy, observation, range

**Difficulty:** ~800 — pure observation

**Naive approach:** Simulate merging in all possible orders. Unnecessary — the answer depends only on the endpoints.

**Complexity:** O(n) time, O(1) space

---

## B — Absolute Cinema

**Key Insight:**
Given n pairs (aᵢ, bᵢ), choose one element from each pair to sum, then add one element from the remaining unchosen values. The optimal strategy: always take `max(aᵢ, bᵢ)` into the sum (greedy — no reason to leave the larger value behind). Then from the unchosen side, take the single largest value: `max over i of min(aᵢ, bᵢ)`.

Answer: `Σ max(aᵢ, bᵢ) + max_i min(aᵢ, bᵢ)`.

**Concepts:** greedy, exchange argument

**Difficulty:** ~1000–1200 — the exchange argument is clean but needs to be seen

**Naive approach:** Try all 2ⁿ selections. The greedy dominance (always take the max) reduces this to O(n).

**Mathematical note:** The exchange argument: if you didn't take `max(aᵢ, bᵢ)` for some i, swapping it in increases the sum by `|aᵢ − bᵢ|` while only potentially changing the bonus term. Since the bonus is a single max over all unchosen elements, the swap can only help.

**Complexity:** O(n) time, O(n) space

---

## C1 — We Be Flipping (Easy Version)

**Key Insight:**
Each operation negates a prefix. Scanning right to left: at each position, decide whether to apply a prefix-negate based on the current sign (accounting for accumulated flips). If the current effective value is positive (we want to minimize the sum), apply the operation. Track a boolean `flipped` state to know the current sign parity.

The backward greedy is optimal because each prefix operation affects all earlier elements — processing right-to-left ensures each decision is made with full knowledge of its downstream effect.

**Concepts:** greedy, backward sweep, parity tracking

**Difficulty:** ~1400 — the backward direction is the key non-obvious choice

**Naive approach:** Try all subsets of prefix operations. O(2ⁿ). The backward greedy resolves this in O(n).

**Failed assumption:** That forward greedy works. Forward processing creates cascading dependencies; backward processing decouples decisions.

**Complexity:** O(n) time, O(n) space (for output)

---

## C2 — We Be Flipping (Hard Version)

**Key Insight:**
Extends C1 by requiring the optimal *value* and operation *ordering* (not just the set of operations). The score is `totalSum + diff − 2·a[M]` where M is the position of the "pivot" operation, and `diff` accumulates `−2·a[j]` for each negative a[j] before M.

Sweep M from left to right, maintaining `diff` as a running sum of contributions from negative elements seen so far. For each positive a[M], compute the candidate score. Take the M that maximizes the score.

Reconstruction: from the chosen M, walk backward to determine which indices to include (want negative values to be flipped), then order operations using a list — positive-index operations go to front, negative-index operations insert after the pivot.

**Concepts:** prefix optimization, greedy sweep, constructive reconstruction

**Difficulty:** ~1800 — the sweep for optimal M is standard; the operation ordering reconstruction is tricky

**Naive approach:** Try all possible M positions and reconstruction orders. The sweep + greedy reconstruction avoids this.

**Complexity:** O(n) time, O(n) space

**Mathematical note:** The score decomposition `totalSum + diff − 2·a[M]` arises because flipping a prefix at M negates a[M] (saving 2·a[M] from the sum) and the `diff` term captures the savings from all negative elements to the left of M that get double-negated back to positive.

---

## D — Me When Median Problem

**Key Insight:**
Binary search on the answer. For a candidate value x, classify each pair as: type 2 (both ≥ x), type 1 (exactly one ≥ x), type 0 (neither ≥ x). The median is ≥ x iff we can choose elements such that the count of "≥ x" values exceeds n/2.

The feasibility check is structural: type-2 positions are "free" (always contribute a ≥ x value). Type-0 positions are "blockers" (never contribute). Type-1 positions are flexible. The key observation: type-2 positions break the array into blocks of non-type-2 elements. A block containing any type-0 position is a "bad block" that consumes one type-2 position to compensate. Feasible iff `type2_count > bad_block_count`.

**Concepts:** binary search on answer, monotone predicate, block decomposition, median characterization

**Difficulty:** ~1900–2100 — the block analysis is the non-trivial step in the monotone check

**Naive approach:** Try all possible element choices. O(2ⁿ). The binary search + structural check reduces to O(n log V).

**Failed assumption:** That the check function needs to consider type-1 positions individually. They're actually irrelevant — only type-2 vs type-0 blocks matter for feasibility.

**Complexity:** O(n log V) time where V = value range, O(n) space

**Mathematical note:** The monotonicity of the check function in x is not immediately obvious. As x increases, type-2 positions can only decrease (fewer pairs have both ≥ x) and type-0 positions can only increase. The `type2_count > bad_block_count` condition is therefore monotonically decreasing in x, validating the binary search.

---

[← Back to root](../../README.md)
