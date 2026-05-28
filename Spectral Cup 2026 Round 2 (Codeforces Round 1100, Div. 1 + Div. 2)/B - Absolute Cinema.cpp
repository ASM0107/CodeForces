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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> b[i];

    long long sumHi = 0;
    int maxLo = 0;
    for (int i = 0; i < n; i++) {
      sumHi += max(a[i], b[i]);
      maxLo = max(maxLo, min(a[i], b[i]));
    }
    cout << sumHi + maxLo << "\n";
  }
  return 0;
}
