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
    int mn = INT_MAX, mx = INT_MIN;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      mn = min(mn, x);
      mx = max(mx, x);
    }
    cout << (mx - mn + 1) / 2 << "\n";
  }
  return 0;
}
