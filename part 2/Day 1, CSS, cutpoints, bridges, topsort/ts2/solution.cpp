#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int INF = 1e18;
int n, m;
vector<vector<int>> g;
vector<int> h, hup, cnt;

void dfs(int v, int anc) {
  hup[v] = h[v];

  for (auto u : g[v]) {
    if (u == anc)
      continue;
    if (h[u] == -1) {
      h[u] = h[v] + 1;
      dfs(u, v);
      hup[v] = min(hup[v], hup[u]);
      if (hup[u] >= h[v] and anc != -1)
        cnt[v]++;
      if (anc == -1)
        cnt[v]++;
    } else
      hup[v] = min(hup[v], h[u]);
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  g.resize(n + 1);
  h.resize(n + 1, -1);
  hup.resize(n + 1);
  cnt.resize(n + 1, 1);
  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to;
    g[from].emplace_back(to);
    g[to].emplace_back(from);
  }

  h[1] = 0;
  dfs(1, -1);
  cnt[1]--;
  int mx = 1, mxi = 0;
  for (int i = 1; i <= n; i++)
    if (cnt[i] > mx) {
      mx = cnt[i];
      mxi = i;
    }
  cout << mxi;
}

// v = from, u = to
// hup[u] > h[v] - bridge
// hup[u] >= h[v] and v!=root - cutpoint
// root - cutpoint if cnt>1 (cnt++ if !used[to] (tree edge))
