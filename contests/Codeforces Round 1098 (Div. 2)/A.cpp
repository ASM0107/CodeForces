#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < n; i++) {
      int w;
      cin >> w;
      if (w == 0)
        a++;
      else if (w == 1)
        b++;
      else
        c++;
    }
    int result = a + min(b, c) + abs(b - c) / 3;
    cout << result << '\n';
  }
  return 0;
}
