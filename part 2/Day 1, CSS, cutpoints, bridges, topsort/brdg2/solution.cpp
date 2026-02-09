#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int INF = 1e18;
int n, m;
vector<set<int>> g;
vector<int> h, hup;
vector<bool> used;
int cnt = 0;

void dfs(int v, int anc) {
  hup[v] = h[v];

  for (auto u : g[v]) {
    if (u == anc)
      continue;
    if (h[u] == -1) {
      h[u] = h[v] + 1;
      dfs(u, v);

      if (hup[u] > h[v])
        cnt++;
      hup[v] = min(hup[v], hup[u]);
    } else
      hup[v] = min(hup[v], h[u]);
  }
}

void dfs2(int v) {
  used[v] = true;
  for (auto u : g[v]) {
    cout << v << ' ' << u << '\n';
    g[u].erase(v);
    if (!used[u])
      dfs2(u);
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  g.resize(n + 1);
  h.resize(n + 1, -1);
  hup.resize(n + 1, -1);
  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to;
    g[from].insert(to);
    g[to].insert(from);
  }

  for (int i = 1; i <= n; i++)
    if (h[i] == -1) {
      h[i] = 0;
      dfs(i, -1);
    }

  if (cnt > 0) {
    cout << 0;
    return 0;
  }
  used.resize(n + 1, false);
  dfs2(1);
}
