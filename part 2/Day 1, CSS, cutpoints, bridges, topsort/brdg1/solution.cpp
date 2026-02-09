#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int INF = 1e18;
int n, m;
vector<vector<pair<int, int>>> g;
vector<int> h, hup;
vector<int> ans;

void dfs(int v, int anc) {
  hup[v] = h[v];

  for (auto pack : g[v]) {
    int u = pack.first, idx = pack.second;
    if (u == anc)
      continue;
    if (h[u] == -1) {
      h[u] = h[v] + 1;
      dfs(u, v);

      if (hup[u] > h[v])
        ans.push_back(idx);
      hup[v] = min(hup[v], hup[u]);
    } else
      hup[v] = min(hup[v], h[u]);
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("bridges.in", "r", stdin);
  freopen("bridges.out", "w", stdout);

  cin >> n >> m;
  g.resize(n + 1);
  h.resize(n + 1, -1);
  hup.resize(n + 1, -1);
  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to;
    g[from].emplace_back(to, i + 1);
    g[to].emplace_back(from, i + 1);
  }

  for (int i = 1; i <= n; i++)
    if (h[i] == -1) {
      h[i] = 0;
      dfs(i, -1);
    }

  cout << ans.size() << endl;
  sort(ans.begin(), ans.end());
  for (auto now : ans)
    cout << now << ' ';
}

// v = from, u = to
// hup[u] > h[v] - bridge
// hup[u] >= h[v] and v!=root - cutpoint
// root - cutpoint if cnt>1 (cnt++ if !used[to] (tree edge))
