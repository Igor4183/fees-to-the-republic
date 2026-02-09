#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int INF = 1e18;

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> tin(n + 1), tout(n + 1);
  vector<pair<bool, int>> l(2 * n);
  for (int i = 0; i < 2 * n; i++) {
    char c;
    int val;
    cin >> c >> val;
    l[i] = {c == '+', val};
    if (c == '+')
      tin[val] = i;
    else
      tout[val] = i;
  }

  vector<vector<int>> g(n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j)
        continue;
      if (tin[i] < tin[j] and tin[j] < tout[i] and tout[i] < tout[j]) {
        g[i].push_back(j);
        g[j].push_back(i);
      }
    }
  }

  queue<int> q;
  vector<int> col(n + 1, -1);
  for (int i = 1; i <= n; i++) {
    if (col[i] != -1)
      continue;
    col[i] = 0;
    q.push(i);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto u : g[v]) {
        if (col[u] == -1) {
          col[u] = 1 - col[v];
          q.push(u);
        } else if (col[u] == col[v]) {
          cout << "*";
          return 0;
        }
      }
    }
  }

  for (int i = 1; i <= n; i++)
    cout << (col[i] == 1 ? "G" : "S");
}
