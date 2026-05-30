#include <bits/stdc++.h>
using namespace std;

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

    // dp[e] = max people seated with e empty tables remaining
    vector<int> dp(x + 1, -1);
    dp[x] = 0;

    for (int i = 0; i < n; i++) {
      vector<int> ndp(x + 1, -1);
      for (int e = 0; e <= x; e++) {
        if (dp[e] < 0)
          continue;
        int seated = dp[e];
        int cap = (x - e) * s - seated;

        // remove person
        ndp[e] = max(ndp[e], seated);

        // seat at empty table (I or A)
        if ((u[i] == 'I' || u[i] == 'A') && e > 0)
          ndp[e - 1] = max(ndp[e - 1], seated + 1);

        // seat at occupied table (E or A)
        if ((u[i] == 'E' || u[i] == 'A') && cap > 0)
          ndp[e] = max(ndp[e], seated + 1);
      }
      dp = ndp;
    }

    int ans = *max_element(dp.begin(), dp.end());
    cout << ans << "\n";
  }
  return 0;
}
