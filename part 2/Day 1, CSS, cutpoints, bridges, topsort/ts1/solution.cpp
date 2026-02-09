#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int INF = 1e18;
int n, m;
vector<vector<int>> g;
vector<int> h, hup;
vector<int> ans;
int cnt;

void dfs(int v, int anc) {
  hup[v] = h[v];

  for (auto u : g[v]) {
    if (u == anc)
      continue;
    if (h[u] == -1) {
      h[u] = h[v] + 1;
      dfs(u, v);

      if (anc == -1)
        cnt++;
      if (hup[u] >= h[v] and anc != -1)
        ans.push_back(v);
      hup[v] = min(hup[v], hup[u]);
    } else
      hup[v] = min(hup[v], h[u]);
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("points.in", "r", stdin);
  freopen("points.out", "w", stdout);

  cin >> n >> m;
  g.resize(n + 1);
  h.resize(n + 1, -1);
  hup.resize(n + 1, -1);
  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to;
    g[from].emplace_back(to);
    g[to].emplace_back(from);
  }

  for (int i = 1; i <= n; i++)
    if (h[i] == -1) {
      cnt = 0;
      h[i] = 0;
      dfs(i, -1);
      if (cnt > 1)
        ans.push_back(i);
    }

  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
  cout << ans.size() << endl;
  for (auto now : ans)
    cout << now << '\n';
}

// v = from, u = to
// hup[u] > h[v] - bridge
// hup[u] >= h[v] and v!=root - cutpoint
// root - cutpoint if cnt>1 (cnt++ if !used[to] (tree edge))
