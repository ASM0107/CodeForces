#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll find_leq(const string &s, const vector<int> &d) {
  int L = s.size();
  int mx = d.back();

  string res;
  bool found = false;

  for (int i = 0; i < L && !found; i++) {
    int target = s[i] - '0';
    int best = -1;
    for (int x : d) {
      if (x <= target) {
        if (i == 0 && L > 1 && x == 0)
          continue;
        best = x;
      }
    }

    if (best < 0) {
      while (!res.empty()) {
        int pos = (int)res.size() - 1;
        int cur = res[pos] - '0';
        res.pop_back();
        int pb = -1;
        for (int x : d) {
          if (x < cur) {
            if (pos == 0 && L > 1 && x == 0)
              continue;
            pb = x;
          }
        }
        if (pb >= 0) {
          res += (char)('0' + pb);
          res += string(L - (int)res.size(), '0' + mx);
          found = true;
          break;
        }
      }
      break;
    } else if (best < target) {
      res += (char)('0' + best);
      res += string(L - (int)res.size(), '0' + mx);
      found = true;
    } else { // best == target
      res += (char)('0' + best);
      if (i == L - 1)
        found = true;
    }
  }

  if (found)
    return stoll(res);

  if (L >= 2 && mx > 0) {
    return stoll(string(L - 1, '0' + mx));
  }
  if (d[0] == 0)
    return 0;

  return -1;
}

ll find_geq(const string &s, const vector<int> &d) {
  int L = s.size();
  int mn = d[0];

  string res;
  bool found = false;

  for (int i = 0; i < L && !found; i++) {
    int target = s[i] - '0';
    int best = -1;
    for (int x : d) {
      if (x >= target) {
        if (i == 0 && L > 1 && x == 0)
          continue;
        if (best < 0)
          best = x;
      }
    }

    if (best < 0) {
      while (!res.empty()) {
        int pos = (int)res.size() - 1;
        int cur = res[pos] - '0';
        res.pop_back();
        int nb = -1;
        for (int x : d) {
          if (x > cur) {
            if (pos == 0 && L > 1 && x == 0)
              continue;
            if (nb < 0)
              nb = x;
          }
        }
        if (nb >= 0) {
          res += (char)('0' + nb);
          res += string(L - (int)res.size(), '0' + mn);
          found = true;
          break;
        }
      }
      break;
    } else if (best > target) {
      res += (char)('0' + best);
      res += string(L - (int)res.size(), '0' + mn);
      found = true;
    } else { // best == target
      res += (char)('0' + best);
      if (i == L - 1)
        found = true;
    }
  }

  if (found)
    return stoll(res);

  int mn_nz = -1;
  for (int x : d)
    if (x > 0) {
      mn_nz = x;
      break;
    }

  if (mn_nz > 0 && L + 1 <= 18) {
    string longer;
    longer += (char)('0' + mn_nz);
    longer += string(L, '0' + mn);
    return stoll(longer);
  }

  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    ll a;
    int n;
    cin >> a >> n;
    vector<int> d(n);
    for (int i = 0; i < n; i++)
      cin >> d[i];

    ll ans = LLONG_MAX;
    string s = to_string(a);

    ll lo = find_leq(s, d);
    if (lo >= 0)
      ans = min(ans, a - lo);

    ll hi = find_geq(s, d);
    if (hi >= 0)
      ans = min(ans, hi - a);

    if (d[0] == 0)
      ans = min(ans, a);

    for (int x : d)
      ans = min(ans, abs(a - (ll)x));

    cout << ans << '\n';
  }
  return 0;
}
