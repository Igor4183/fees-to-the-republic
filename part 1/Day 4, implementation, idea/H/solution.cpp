#include <bits/stdc++.h>
#define int int64_t

using namespace std;

void solve() {
  int r = 0;
  for (int k = 0; k < 30; k++) {
    int a = (1 << k) - r, b = a + (1 << (k + 1));
    cout << "? " << a << ' ' << b << '\n';
    cout.flush();
    int res;
    cin >> res;
    if (res == (1 << (k + 1)))
      r += (1 << k);
  }
  cout << "! " << r << '\n';
  cout.flush();
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--)
    solve();
}