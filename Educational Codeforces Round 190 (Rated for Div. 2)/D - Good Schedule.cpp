#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  while (T--) {
    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i <= n; i++)
      cin >> b[i];

    vector<vector<pair<int, bool>>> events(n + 2);
    for (int i = 1; i <= n; i++) {
      if (a[i] == b[i]) {
        events[a[i]].push_back({i, true});
      } else {
        events[a[i]].push_back({i, false});
        events[b[i]].push_back({i, false});
      }
    }

    vector<vector<long long>> gval(n + 2);

    auto query_g = [&](int pos, int v) -> long long {
      if (v > n)
        return (long long)n;
      auto &ev = events[v];
      int idx = (int)(lower_bound(ev.begin(), ev.end(), make_pair(pos, false)) -
                      ev.begin());
      if (idx == (int)ev.size())
        return (long long)n;
      return gval[v][idx];
    };

    for (int v = n; v >= 1; v--) {
      auto &ev = events[v];
      gval[v].resize(ev.size());
      for (int j = 0; j < (int)ev.size(); j++) {
        if (ev[j].second)
          gval[v][j] = query_g(ev[j].first + 1, v + 1);
        else
          gval[v][j] = ev[j].first - 1;
      }
    }

    long long ans = 0;
    auto &event1 = events[1];

    auto sum_range = [](long long a, long long b, long long C) -> long long {
      if (a > b)
        return 0LL;
      long long bp = min(b, C);
      if (bp < a)
        return 0LL;
      long long lo = C - bp + 1, hi = C - a + 1;
      return (hi - lo + 1) * (lo + hi) / 2;
    };

    int prev = 0;
    for (int j = 0; j < (int)event1.size(); j++) {
      ans += sum_range(prev + 1, event1[j].first, gval[1][j]);
      prev = event1[j].first;
    }
    ans += sum_range(prev + 1, n, n);

    cout << ans << "\n";
  }
  return 0;
}
