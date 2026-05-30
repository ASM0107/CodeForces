#include <bits/stdc++.h>
using namespace std;

int simulate(const string &u, int n, int x, int s, int k_A) {
  int e = x, seated = 0, a_opened = 0;
  long long c = 0;
  for (int i = 0; i < n; i++) {
    if (u[i] == 'I') {
      if (e > 0) {
        e--;
        c += s - 1;
        seated++;
      }
    } else if (u[i] == 'E') {
      if (c > 0) {
        c--;
        seated++;
      }
    } else {
      if (a_opened < k_A && e > 0) {
        a_opened++;
        e--;
        c += s - 1;
        seated++;
      } else if (c > 0) {
        c--;
        seated++;
      }
    }
  }
  return seated;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, x, s;
    cin >> n >> x >> s;
    string u;
    cin >> u;

    int count_A = count(u.begin(), u.end(), 'A');
    int hi = min(count_A, x);

    int lo = 0;
    while (hi - lo > 2) {
      int m1 = lo + (hi - lo) / 3;
      int m2 = hi - (hi - lo) / 3;
      if (simulate(u, n, x, s, m1) < simulate(u, n, x, s, m2))
        lo = m1;
      else
        hi = m2;
    }

    int ans = 0;
    for (int k = lo; k <= hi; k++)
      ans = max(ans, simulate(u, n, x, s, k));
    cout << ans << "\n";
  }
  return 0;
}
