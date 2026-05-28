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
    for (int i = 0; i < n; i++)
      cin >> a[i];
    vector<int> ops;
    bool flipped = false;
    for (int i = n - 1; i >= 0; i--) {
      int cur = flipped ? -a[i] : a[i];
      if (cur > 0) {
        ops.push_back(i + 1);
        flipped = !flipped;
      }
    }

    cout << ops.size() << "\n";
    for (int i = 0; i < (int)ops.size(); i++) {
      cout << ops[i];
      if (i + 1 < (int)ops.size())
        cout << ' ';
    }
    if (!ops.empty())
      cout << "\n";
  }
  return 0;
}
