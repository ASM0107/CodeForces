#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    string s;
    cin >> s;

    int fours = count(s.begin(), s.end(), '4');

    string r;
    for (char c : s)
      if (c != '4')
        r += c;
    int m = r.size();

    vector<int> cnt13(m + 1, 0), cnt2(m + 1, 0);
    for (int i = 0; i < m; i++) {
      cnt13[i + 1] = cnt13[i] + (r[i] == '1' || r[i] == '3');
      cnt2[i + 1] = cnt2[i] + (r[i] == '2');
    }

    int best = m;
    for (int p = 0; p <= m; p++)
      best = min(best, cnt13[p] + cnt2[m] - cnt2[p]);

    printf("%d\n", fours + best);
  }
  return 0;
}
