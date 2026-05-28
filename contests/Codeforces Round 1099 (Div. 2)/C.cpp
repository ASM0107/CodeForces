#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a)
      cin >> x;

    unordered_map<long long, pair<long long, int>> mp;
    mp.reserve(1 << 12);
    mp.max_load_factor(0.25);

    for (int i = 0; i < n; i++) {
      long long x = a[i];
      int ops = 0;
      bool saw2 = false;
      while (x != 1) {
        if (x == 2)
          saw2 = true;
        mp[x].first += ops;
        mp[x].second++;
        if (x & 1)
          x++;
        else
          x >>= 1;
        ops++;
      }
      mp[1].first += ops;
      mp[1].second++;
      if (!saw2) {
        mp[2].first += ops + 1;
        mp[2].second++;
      }
    }

    long long ans = LLONG_MAX;
    for (auto &[val, p] : mp) {
      if (p.second == n)
        ans = min(ans, p.first);
    }

    cout << ans << "\n";
    mp.clear();
  }
  return 0;
}
