#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;
  while (t--) {
    long long n, x1, x2, k;
    cin >> n >> x1 >> x2 >> k;
    long long d = abs(x1 - x2);
    d = min(d, n - d);
    if (n >= 4)
      cout << d + k << '\n';
    else
      cout << d << '\n';
  }
  return 0;
}
