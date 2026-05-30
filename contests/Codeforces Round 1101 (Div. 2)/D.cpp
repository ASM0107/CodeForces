#include <bits/stdc++.h>
using namespace std;

int a[21];
vector<tuple<int, int, int>> moves;
bool possible;

void solve(int lo, int hi, int src, int dst, int aux) {
  if (lo > hi || !possible)
    return;
  int K = hi - 1 - a[hi];
  if (K < lo - 1) {
    possible = false;
    return;
  }

  if (K == hi - 1) {
    solve(lo, hi - 1, src, aux, dst);
    moves.push_back({hi, src, dst});
    solve(lo, hi - 1, aux, dst, src);
  } else {
    solve(lo, K, src, aux, dst);
    moves.push_back({hi, src, dst});
    solve(lo, K, aux, src, dst);
    solve(lo, hi - 1, src, dst, aux);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];

    moves.clear();
    possible = true;
    solve(1, n, 1, 3, 2);

    if (!possible) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
      cout << moves.size() << "\n";
      for (auto &[id, from, to] : moves)
        cout << id << " " << from << " " << to << "\n";
    }
  }
  return 0;
}
