# Codeforces Round 1098 (Div. 2)

**Contest:** [#2228](https://codeforces.com/contest/2228) · **Rank:** 504 · **Solved:** 5/8 · **Rating:** 0 → 661

---

## A — Marisa Steals Reimu's Takeout

**Key Insight:**
Items weigh 0, 1, or 2. A box holds exactly weight 2. Weight-0 items are free (box each alone). Pair each 1 with a 2. Leftover same-weight items group in threes (three 1s or three 2s fill 1.5 boxes, but since 3 × 1 = 3 needs ⌊3/3⌋ = 1 extra box pair... actually: leftover unpaired items of the same kind can only combine in groups of 3 to fill a bag). The formula distills to `count(0) + min(count(1), count(2)) + |count(1) - count(2)| / 3`.

**Concepts:** greedy, counting, modular arithmetic

**Difficulty:** ~800 — straightforward greedy counting

**Naive approach:** Try all possible pairings via brute force. Fails for large n due to exponential combinations.

**Complexity:** O(n) time, O(1) space

---

## B — Remilia Plays Soku

**Key Insight:**
On a circular ring of size n, the minimum distance between two positions is `min(|x₁−x₂|, n−|x₁−x₂|)`. The k extra moves can always be absorbed without net effect when n ≥ 4 (move away and back), so the answer is `d + k`. When n < 4 (specifically n = 3), any extra move is forced to change position, and k moves just oscillate — but k = 0 always, so `d` suffices.

**Concepts:** circular distance, case analysis on small n

**Difficulty:** ~900 — observation about absorbing extra moves on large rings

**Naive approach:** Simulate all possible movement sequences. Unnecessary — the circular distance formula with case split handles it.

**Complexity:** O(1) per test case

---

## C1/C2 — Cirno and Number (Easy/Hard Version)

**Key Insight:**
Given a target number a and a set of allowed digits, find the closest number composed entirely of those digits. The key is a digit-by-digit greedy construction with backtracking: build the largest number ≤ a (`find_leq`) and the smallest number ≥ a (`find_geq`), then take whichever is closer.

For `find_leq`: scan left to right, try to match each digit. When forced to go lower, fill the remaining positions with the maximum allowed digit. If no digit fits, backtrack — pop the last placed digit, decrement it to the next smaller allowed digit, then fill the rest with max.

For `find_geq`: symmetric logic — go higher when forced, fill rest with minimum, backtrack upward if stuck.

Edge cases: leading zeros, the number 0 itself, and the possibility of needing a shorter/longer representation.

**Concepts:** digit construction, greedy with backtracking, string manipulation

**Difficulty:** ~1600–1800 — the backtracking logic and edge cases make this implementation-heavy

**Naive approach:** Iterate outward from a checking every number. O(a) worst case, way too slow for a up to 10^18.

**Failed assumption:** That you only need to check same-length numbers. Sometimes the answer has fewer or more digits.

**Complexity:** O(L²) per query where L = number of digits (≤ 18), effectively O(1) per query

**Mathematical note:** The greedy-with-backtracking approach is essentially a constrained digit DP done eagerly. The invariant is that once you place a digit strictly less than the target, all subsequent digits should be maximized (for ≤) or minimized (for ≥). Backtracking is only needed when no valid digit exists at a position, which happens at most L times total.

---

## D — Sanae, Cross and Color

**Key Insight:**
After coordinate-compressing Y values and grouping points by X coordinate, each X-group contributes a range [min_y, max_y] in compressed space. The problem reduces to counting valid vertical split positions. At each split between consecutive X-groups, compute the overlap between the prefix range [pmn, pmx] and suffix range [smn, smx]. The answer accumulates `max(0, min(pmx, smx) - max(pmn, smn))` across all splits.

**Concepts:** coordinate compression, prefix/suffix min-max arrays, sweep

**Difficulty:** ~1800–2000 — requires combining several standard techniques cleanly

**Naive approach:** Try all possible dividing lines and compute ranges on both sides. O(n²) without prefix/suffix precomputation.

**Complexity:** O(n log n) time (sorting), O(n) space

**Mathematical note:** The prefix/suffix arrays form a monotone structure — `pmx` is non-decreasing, `pmn` is non-increasing, and their suffix counterparts are symmetric. This means the overlap region can be computed locally at each split without revisiting earlier data.

---

[← Back to root](../../README.md)
