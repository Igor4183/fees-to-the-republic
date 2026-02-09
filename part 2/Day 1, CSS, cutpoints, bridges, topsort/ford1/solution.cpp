#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("negcycle.in", "r", stdin);
  freopen("negcycle.out", "w", stdout);

  int n;
  cin >> n;
  vector<vector<pair<int, int>>> g(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int w;
      cin >> w;
      if (w != 1e5)
        g[i].emplace_back(j, w);
    }
  }

  vector<int> d(n, 0), p(n, -1);

  int x;
  for (int i = 0; i < n; i++) {
    x = -1;
    for (int v = 0; v < n; v++) {
      for (auto [to, w] : g[v]) {
        if (d[to] > d[v] + w) {
          d[to] = d[v] + w;
          p[to] = v;
          x = to;
        }
      }
    }
  }

  if (x == -1) {
    cout << "NO\n";
    return 0;
  }

  int y = x;
  for (int i = 0; i < n; i++)
    y = p[y];

  vector<int> cycle;
  int cur = y;
  do {
    cycle.push_back(cur);
    cur = p[cur];
  } while (cur != y);
  reverse(cycle.begin(), cycle.end());

  cout << "YES\n";
  cout << cycle.size() << "\n";
  for (int v : cycle)
    cout << (v + 1) << " ";
}
