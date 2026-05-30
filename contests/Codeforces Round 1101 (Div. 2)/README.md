# Codeforces Round 1101 (Div. 2)

**Contest:** [Codeforces Round 1101](https://codeforces.com/contest/2242) · **Solved:** 6/6

---

## A — Convergence

**Key Insight:**
Sort the array and pick a target value that minimizes the cost. Each group call handles 2 friends. If we pick target value `p`, friends on opposite sides can be paired — one call sends both to `p` (since `p` lies between them). The bottleneck is the larger side. Cost = `max(L, R)` where `L` = count strictly less than `p`, `R` = count strictly greater. Minimize over all values in the array.

**Concepts:** sorting, greedy pairing, median-style optimization

**Difficulty:** ~800–1000 — the pairing observation is the crux; without it you'd think the answer is `n - max_freq`

**Naive approach:** Simulate all possible pairing strategies. The sorted structure reveals that opposite-side pairs are always optimal.

**Failed assumption:** That the answer is `n - max_freq` (each friend needs one individual call). Pairing friends from opposite sides halves the cost for balanced splits.

**Complexity:** O(n log n) time, O(n) space

**Mathematical note:** For distinct values, the optimal target is the median, giving answer `⌈(n−1)/2⌉`. Duplicates near the median reduce this further. The `max(first_index, n − 1 − last_index)` formula captures both effects in one pass over distinct values.

---

## B — Cake Leveling

**Key Insight:**
When sweeping left to right with knife at height `h`, position `j` accumulates all excess from positions `1..j−1`. The cumulative excess at position `j` is `sum(a[1..j]) − j·h`. For the result to be level at height `h`, this must be non-negative for every `j`. This gives the constraint `h ≤ ⌊sum(a[1..j]) / j⌋` for all `j`.

The answer for prefix `i` is simply the running minimum of `⌊prefix_sum(j) / j⌋` for `j = 1..i`.

**Concepts:** prefix sums, sweep, constraint derivation from simulation

**Difficulty:** ~1000–1200 — the sweep simulation is easy to reason about once you formalize the excess flow

**Naive approach:** Binary search on `h` for each prefix and simulate. O(n² log A) — unnecessary once the closed-form is derived.

**Failed assumption:** That the leveling process is complex. The left-to-right sweep means excess accumulates predictably — it's just prefix sums.

**Complexity:** O(n) time, O(1) space (streaming computation)

**Mathematical note:** `⌊min(a/b, c/d)⌋ = min(⌊a/b⌋, ⌊c/d⌋)` since floor is monotone. This justifies maintaining a running minimum of floored ratios rather than tracking exact rational values.

---

## C1 — Seating Arrangement (Easy Version)

**Key Insight:**
Introverts (I) must sit at empty tables, extroverts (E) must sit at non-empty tables, ambiverts (A) can do either. I and E decisions are forced. Only A decisions matter.

The state is (empty tables `e`), and capacity at non-empty tables is derivable as `(x − e) · s − seated`. This reduces the DP to 1D: `dp[e]` = max people seated with `e` empty tables remaining.

For each person, transitions are:
- **I:** `dp[e] → dp[e−1] + 1` (forced open, if `e > 0`)
- **E:** `dp[e] → dp[e] + 1` (forced fill, if capacity > 0)
- **A:** try both I and E transitions, take best

**Concepts:** DP with derived state, resource modeling (empty tables vs capacity)

**Difficulty:** ~1400–1600 — the insight that capacity = `(x−e)·s − seated` collapses a 2D DP to 1D

**Naive approach:** Track full table occupancies. Exponential state space.

**Failed assumption:** That you need to track capacity independently. It's fully determined by `e` and `seated`.

**Complexity:** O(n · x) time, O(x) space — sufficient for n, x ≤ 3000

---

## C2 — Seating Arrangement (Hard Version)

**Key Insight:**
The C1 DP is O(n · x), too slow for n, x up to 2·10⁵. The key observation: I's always open tables (forced), E's always fill capacity (forced). The only free parameter is how many A's open tables vs fill capacity.

Define `k_A` = number of ambiverts that open tables. For a fixed `k_A`, the simulation is deterministic and O(n): the first `k_A` ambiverts (in sequence order) open tables, the rest use capacity.

The answer as a function of `k_A` is **unimodal** — increasing `k_A` creates more capacity (helping future E's) but consumes empty tables (potentially displacing future I's). The marginal benefit decreases as early A-openers have the most impact. This enables **ternary search** over `k_A`.

**Concepts:** ternary search on unimodal function, greedy simulation, parameter space reduction

**Difficulty:** ~1800–2000 — recognizing that the multi-dimensional DP collapses to a 1D unimodal search is the breakthrough

**Naive approach:** The C1 DP at O(n · x). Too slow for hard constraints.

**Failed assumption:** That a purely local greedy (e.g., "always prefer non-empty") works. Counterexamples exist in both directions — the optimal A behavior depends on the global distribution of future I's and E's.

**Bug Trap (Integer Overflow):** Since `x` and `s` can be up to 2·10⁵, the total capacity `c` can reach `x × s = 4·10¹⁰`. Using a 32-bit `int` for capacity will overflow `INT_MAX` (~2·10⁹), wrap around to negative numbers, and break the `c > 0` checks, leading to a WA. Capacity must be tracked using `long long`.

**Complexity:** O(n log n) time (ternary search × O(n) simulation), O(n) space

**Mathematical note:** Unimodality follows from diminishing marginal returns: each additional A-opener displaces at most 1 future I but creates s−1 capacity. The first A-opener to switch creates capacity where it's most needed (before E's that were starved); later switches have less impact.

---

## D — Magical Tiered Cake

**Key Insight:**
This is a **generalized Tower of Hanoi**, but with a twist. The problem says: "choose exactly one movable layer... and move it." If layer `hi` is pulled out from under other layers, the layers above it *fall down and stay on the current peg*. 

The recursive decomposition to move stack `lo..hi` from `src` to `dst`:
1. To move `hi`, it needs exactly `a[hi]` layers above it. If `a[hi] > hi - lo`, it's **impossible**.
2. We must remove the top `K = (hi - lo) - a[hi]` layers from `src`. These are exactly layers `lo..lo+K-1`.
3. If `K == hi - lo` (i.e., `a[hi] == 0`), this is standard Hanoi: move `lo..hi-1` to `aux`, move `hi` to `dst`, then move `lo..hi-1` from `aux` to `dst`.
4. If `K < hi - lo` (i.e., `a[hi] > 0`), we move `lo..lo+K-1` to `aux`. Then move `hi` to `dst`. Now `src` still has the `a[hi]` layers. The key trick is to move `lo..lo+K-1` **back from `aux` to `src`**. Since they are the smallest layers, they can safely sit on top of the remaining layers at `src`! Now all layers `lo..hi-1` are back together at `src`, and `aux` is empty. We can then do a standard Hanoi to move `lo..hi-1` from `src` to `dst`.

**Concepts:** recursion, Tower of Hanoi generalization, divide and conquer, impossibility detection

**Difficulty:** ~2000–2200 — realizing that pulling a layer out from the middle is valid, and that the top subset can be temporarily parked and returned to the source peg.

**Naive approach:** Trying to move the remaining `a[hi]` layers to `dst` while `aux` is occupied by the top `K` layers. This violates Hanoi rules because `aux` contains smaller layers, so it's blocked.

**Failed assumption:** That the standard Hanoi sequence `solve(K) -> move hi -> solve(remaining)` works. `aux` is blocked by the top `K` layers. The breakthrough is that you must reunite the stack at `src` before moving the rest. 

**Complexity:** O(2^n) time and space. Wait, does returning the layers to `src` exceed `2^n - 1` moves? No! The math works perfectly: `M(n) = 2*M(K) + 1 + M(n-1)`. Since `K <= n-2` (due to `a[hi] > 0`), `M(n) <= 2*(2^{n-2} - 1) + 1 + (2^{n-1} - 1) = 2^n - 2`. We strictly stay under the `2^n` budget!

---

[← Back to root](../../README.md)
