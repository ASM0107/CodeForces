#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
      cin >> x[i] >> y[i];

    vector<int> ys = y;
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int p = ys.size();

    vector<pair<int, int>> pts(n);
    for (int i = 0; i < n; i++)
      pts[i] = {x[i], y[i]};
    sort(pts.begin(), pts.end());

    vector<int> gmn, gmx;
    for (int i = 0; i < n;) {
      int j = i, lo = INT_MAX, hi = INT_MIN;
      while (j < n && pts[j].first == pts[i].first) {
        int r =
            lower_bound(ys.begin(), ys.end(), pts[j].second) - ys.begin() + 1;
        lo = min(lo, r);
        hi = max(hi, r);
        j++;
      }
      gmn.push_back(lo);
      gmx.push_back(hi);
      i = j;
    }
    int m = gmn.size();

    if (m < 2 || p < 2) {
      cout << 0 << '\n';
      continue;
    }

    vector<int> pmn(m), pmx(m), smn(m), smx(m);
    pmn[0] = gmn[0];
    pmx[0] = gmx[0];
    for (int i = 1; i < m; i++) {
      pmn[i] = min(pmn[i - 1], gmn[i]);
      pmx[i] = max(pmx[i - 1], gmx[i]);
    }
    smn[m - 1] = gmn[m - 1];
    smx[m - 1] = gmx[m - 1];
    for (int i = m - 2; i >= 0; i--) {
      smn[i] = min(smn[i + 1], gmn[i]);
      smx[i] = max(smx[i + 1], gmx[i]);
    }

    ll ans = 0;
    for (int i = 1; i < m; i++) {
      int lo = max(pmn[i - 1], smn[i]);
      int hi = min(pmx[i - 1], smx[i]);
      if (hi > lo)
        ans += hi - lo;
    }
    cout << ans << '\n';
  }
  return 0;
}
