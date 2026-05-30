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
    vector<int> a(n);
    for (auto &x : a)
      cin >> x;

    sort(a.begin(), a.end());

    int ans = n;
    for (int i = 0; i < n;) {
      int j = i;
      while (j < n && a[j] == a[i])
        j++;
      // a[i] is first occurrence, a[j-1] is last occurrence of this value
      int L = i;     // elements strictly less
      int R = n - j; // elements strictly greater
      ans = min(ans, max(L, R));
      i = j;
    }
    cout << ans << "\n";
  }
  return 0;
}
