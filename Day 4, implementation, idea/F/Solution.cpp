#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, p;
  cin >> n >> p;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int v, u;
    cin >> v >> u;
    g[v].push_back(u);
    g[u].push_back(v);
  }
  if (n == 1) {
    cout << 0;
    return 0;
  }

  int cnt = 0;
  for (int i = 0; i < n; i++)
    if (g[i].size() == 1)
      cnt++;

  cout << 2 * (p / cnt) + min(2LL, p % cnt);
}
