#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int multiTestQ;
  cin >> multiTestQ;

  while (multiTestQ--) {
    int n;
    cin >> n;

    long long S = 0, c_max = 0, total_slots = 0;
    int pairs_count = 0, ones = 0;

    for (int i = 0; i < n; i++) {
      long long c;
      cin >> c;
      if (c >= 2) {
        S += c;
        pairs_count++;
        c_max = max(c_max, c);
        total_slots += c / 2 - 1;
      } else {
        ones++;
      }
    }

    long long ans = 0;

    if (pairs_count == 0) {
      ans = 0;
    } else if (pairs_count == 1) {
      if (c_max >= 3) {
        ans = c_max + min((long long)ones, c_max / 2);
      } else {
        ans = (ones >= 1) ? 3 : 0;
      }
    } else {
      ans = S + min((long long)ones, total_slots);
    }

    cout << ans << "\n";
  }

  return 0;
}