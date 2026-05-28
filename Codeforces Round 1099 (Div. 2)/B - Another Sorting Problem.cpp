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

    vector<int> inversions;
    for (int i = 0; i + 1 < n; i++) {
      if (a[i] > a[i + 1])
        inversions.push_back(i);
    }

    if (inversions.empty()) {
      cout << "YES\n";
      continue;
    }

    bool hasAdjacentInversions = false;
    for (int i = 0; i + 1 < (int)inversions.size(); i++) {
      if (inversions[i + 1] == inversions[i] + 1) {
        hasAdjacentInversions = true;
        break;
      }
    }
    if (hasAdjacentInversions) {
      cout << "NO\n";
      continue;
    }

    long long kMin = 0;
    for (int pos : inversions)
      kMin = max(kMin, (long long)(a[pos] - a[pos + 1]));

    long long kMax = LLONG_MAX;
    for (int i = 0; i + 1 < (int)inversions.size(); i++) {
      int left = inversions[i] + 1;
      int right = inversions[i + 1];
      long long largestGap = LLONG_MIN;
      for (int j = left; j < right; j++) {
        largestGap = max(largestGap, (long long)(a[j + 1] - a[j]));
      }
      kMax = min(kMax, largestGap);
    }

    cout << (kMin <= kMax ? "YES" : "NO") << "\n";
  }
  return 0;
}
