#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k;
  cin >> n >> k;
  if (k > n) {
    cout << "NO\n";
    return;
  }

  if (n % 2 == 1 and k % 2 == 1 or n % 2 == 0 and k % 2 == 0) {
    cout << "YES\n";
    for (int i = 0; i < k - 1; i++)
      cout << "1 ";
    cout << n - k + 1 << '\n';
    return;
  }
  if (n % 2 == 0 and 2 * k <= n) {
    cout << "YES\n";
    for (int i = 0; i < k - 1; i++)
      cout << "2 ";
    cout << n - 2 * (k - 1) << '\n';
    return;
  }

  cout << "NO\n";
  return;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
