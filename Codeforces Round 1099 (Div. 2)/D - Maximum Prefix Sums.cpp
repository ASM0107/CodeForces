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
    string s;
    cin >> s;
    vector<long long> a(n), c(n);
    for (auto &x : a)
      cin >> x;
    for (auto &x : c)
      cin >> x;

    bool ok = true;
    for (int i = 1; i < n; i++)
      if (c[i] < c[i - 1])
        ok = false;

    vector<long long> ans(n);
    long long b = 0;
    int i = 0;

    while (i < n && ok) {
      if (i == 0 || c[i] > c[i - 1]) {
        if (s[i] == '1') {
          if (b + a[i] != c[i]) {
            ok = false;
            break;
          }
          ans[i] = a[i];
        } else {
          ans[i] = c[i] - b;
        }
        b = c[i];
        i++;
      } else if (s[i] == '1') {
        b += a[i];
        if (b > c[i]) {
          ok = false;
          break;
        }
        ans[i] = a[i];
        i++;
      } else {
        long long upper = c[i];
        long long sum = 0;
        int j = i + 1;
        bool has_fixed = false;
        long long fixed_val = 0;

        while (j < n && s[j] == '1') {
          sum += a[j];
          upper = min(upper, c[j] - sum);
          if (c[j] > c[j - 1]) {
            long long fv = c[j] - sum;
            if (has_fixed && fixed_val != fv) {
              ok = false;
              break;
            }
            has_fixed = true;
            fixed_val = fv;
          }
          j++;
        }
        if (!ok)
          break;

        long long new_b;
        if (has_fixed) {
          new_b = fixed_val;
          if (new_b > upper) {
            ok = false;
            break;
          }
        } else {
          new_b = upper;
        }

        ans[i] = new_b - b;
        b = new_b;
        i++;

        while (i < j) {
          b += a[i];
          ans[i] = a[i];
          i++;
        }
      }
    }

    if (ok) {
      cout << "Yes\n";
      for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i == n - 1];
    } else {
      cout << "No\n";
    }
  }
  return 0;
}
