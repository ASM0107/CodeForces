#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    long long n, a, b;
    scanf("%lld %lld %lld", &n, &a, &b);
    long long groups = n / 3;
    long long rem = n % 3;
    long long cost = groups * min(b, 3 * a);
    if (rem > 0)
      cost += min(rem * a, b);
    printf("%lld\n", cost);
  }
  return 0;
}
