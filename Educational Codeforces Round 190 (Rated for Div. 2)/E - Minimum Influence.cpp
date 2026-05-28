#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;
  vector<long long> p(n), c(n);
  for (int i = 0; i < n; i++)
    cin >> p[i];
  for (int i = 0; i < n; i++)
    cin >> c[i];

  vector<pair<long long, long long>> pts(n);
  for (int i = 0; i < n; i++)
    pts[i] = {p[i], c[i]};
  sort(pts.begin(), pts.end());

  vector<long long> pp, cc, sc;
  long long minc = LLONG_MAX;
  for (auto &[px, cx] : pts) {
    if (cx < minc) {
      pp.push_back(px);
      cc.push_back(cx);
      minc = cx;
    }
  }
  int k = pp.size();
  sc.resize(k);
  for (int i = 0; i < k; i++)
    sc[i] = pp[i] + cc[i];

  int LOG = 1;
  while ((1 << LOG) <= k)
    LOG++;
  vector<vector<long long>> sparse(LOG, vector<long long>(k));
  sparse[0] = sc;
  for (int j = 1; j < LOG; j++)
    for (int i = 0; i + (1 << j) <= k; i++)
      sparse[j][i] = min(sparse[j - 1][i], sparse[j - 1][i + (1 << (j - 1))]);

  auto rmq = [&](int l, int r) -> long long {
    if (l > r)
      return LLONG_MAX;
    int j = __lg(r - l + 1);
    return min(sparse[j][l], sparse[j][r - (1 << j) + 1]);
  };

  auto bsearch_dec = [&](long long val) -> int {
    int lo = 0, hi = k;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (cc[mid] >= val)
        lo = mid + 1;
      else
        hi = mid;
    }
    return lo;
  };

  int m;
  cin >> m;
  vector<long long> tp(m), tc(m), d(m);
  for (int i = 0; i < m; i++)
    cin >> tp[i];
  for (int i = 0; i < m; i++)
    cin >> tc[i];
  for (int i = 0; i < m; i++)
    cin >> d[i];

  for (int j = 0; j < m; j++) {
    long long tpj = tp[j], tcj = tc[j], dj = d[j];
    int i1 = (int)(lower_bound(pp.begin(), pp.end(), tpj) - pp.begin());
    int i2 = (int)(lower_bound(pp.begin(), pp.end(), tpj + dj) - pp.begin());
    int j1 = bsearch_dec(tcj + dj);
    int j2 = bsearch_dec(tcj);

    long long ans = LLONG_MAX;

    auto check_range = [&](int lo, int hi, int pr, int cr) {
      if (lo >= hi)
        return;
      long long fp, gc;
      if (pr == 0)
        fp = 0;
      else if (pr == 2)
        fp = tpj + dj;
      else
        fp = -1;
      if (cr == 2)
        gc = 0;
      else if (cr == 0)
        gc = tcj + dj;
      else
        gc = -1;

      long long val;
      if (fp >= 0 && gc >= 0)
        val = fp + gc;
      else if (fp >= 0 && gc < 0)
        val = fp + cc[hi - 1];
      else if (fp < 0 && gc >= 0)
        val = pp[lo] + gc;
      else
        val = rmq(lo, hi - 1);
      ans = min(ans, val);
    };

    int p_bounds[4] = {0, i1, i2, k};
    int c_bounds[4] = {0, j1, j2, k};
    for (int pr = 0; pr < 3; pr++)
      for (int cr = 0; cr < 3; cr++) {
        int lo = max(p_bounds[pr], c_bounds[cr]);
        int hi = min(p_bounds[pr + 1], c_bounds[cr + 1]);
        check_range(lo, hi, pr, cr);
      }

    cout << ans << "\n";
  }
  return 0;
}
