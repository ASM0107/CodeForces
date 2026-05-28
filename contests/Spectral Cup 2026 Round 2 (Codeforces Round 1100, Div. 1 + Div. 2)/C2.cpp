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
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];

    long long totalSum = 0;
    for (int i = 0; i < n; i++)
      totalSum += a[i];

    long long bestScore = totalSum;
    int bestM = -1;
    long long diff = 0;
    for (int M = 0; M < n; M++) {
      if (a[M] > 0) {
        long long sc = totalSum + diff - 2 * a[M];
        if (sc > bestScore) {
          bestScore = sc;
          bestM = M;
        }
      }
      if (a[M] < 0)
        diff += -2 * a[M];
    }

    if (bestM == -1) {
      cout << 0 << "\n";
      continue;
    }

    vector<int> d(n, 0);
    d[bestM] = 1;
    int cur_parity = 1;
    for (int j = bestM - 1; j >= 0; j--) {
      int want = (a[j] < 0) ? 1 : 0;
      d[j] = want ^ cur_parity;
      cur_parity = want;
    }

    vector<int> S;
    for (int i = 0; i < n; i++)
      if (d[i])
        S.push_back(i);

    sort(S.begin(), S.end(), greater<int>());
    list<int> order;
    for (int i = 0; i < (int)S.size(); i++) {
      if (i == 0) {
        order.push_back(S[i]);
      } else if (a[S[i]] > 0) {
        order.push_front(S[i]);
      } else {
        auto it = order.begin();
        ++it;
        order.insert(it, S[i]);
      }
    }

    cout << order.size() << "\n";
    bool first = true;
    for (int idx : order) {
      if (!first)
        cout << ' ';
      cout << idx + 1;
      first = false;
    }
    if (!order.empty())
      cout << "\n";
  }
  return 0;
}
