#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int MOD = 1e9 + 7;

int binpow(int val, int deg) {
  int res = 1;
  while (deg) {
    if (deg & 1)
      res = (res * val) % MOD;
    val = (val * val) % MOD;
    deg >>= 1;
  }
  return res;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  if (n == 0) {
    cout << 1;
    return 0;
  }
  cout << (binpow(2, 2 * n - 1) + binpow(2, n - 1)) % MOD;
}
