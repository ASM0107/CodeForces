#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int tests;
  cin >> tests;
  while (tests--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> b[i];

    vector<int> candidates;
    for (int i = 0; i < n; i++) {
      candidates.push_back(a[i]);
      candidates.push_back(b[i]);
    }
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()),
                     candidates.end());

    auto check = [&](int x) -> bool {
      int type2_count = 0;
      int zero_blocks = 0;
      bool in_non2_block = false;
      bool block_has_zero = false;

      for (int i = 0; i < n; i++) {
        int type = (a[i] >= x) + (b[i] >= x);
        if (type == 2) {
          type2_count++;
          if (in_non2_block && block_has_zero)
            zero_blocks++;
          in_non2_block = false;
          block_has_zero = false;
        } else {
          in_non2_block = true;
          if (type == 0)
            block_has_zero = true;
        }
      }
      if (in_non2_block && block_has_zero)
        zero_blocks++;

      return type2_count > zero_blocks;
    };

    int lo = 0, hi = (int)candidates.size() - 1, ans = candidates[0];
    while (lo <= hi) {
      int mid = (lo + hi) / 2;
      if (check(candidates[mid])) {
        ans = candidates[mid];
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
