#include <bits/stdc++.h>
#define int int64_t

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  n %= 1500;
  vector<int> fib(1500);
  fib[0] = 0;
  fib[1] = 1;
  for (int i = 2; i <= n; i++) {
    fib[i] = (fib[i - 1] + fib[i - 2]) % 1000;
  }
  cout << fib[n];
}
