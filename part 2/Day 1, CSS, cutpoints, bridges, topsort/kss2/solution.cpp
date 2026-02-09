#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int INF = 1e18;
int n, m;
vector<set<int>> g;
vector<int> h, hup;
vector<pair<int, int>> br;

vector<int> comp;
vector<vector<int>> cg;
int cmp_id = 0;

void dfs(int v, int anc) {
  hup[v] = h[v];

  for (auto u : g[v]) {
    if (u == anc)
      continue;
    if (h[u] == -1) {
      h[u] = h[v] + 1;
      dfs(u, v);

      if (hup[u] > h[v])
        br.emplace_back(v, u);
      hup[v] = min(hup[v], hup[u]);
    } else
      hup[v] = min(hup[v], h[u]);
  }
}

void dfs2(int v) {
  comp[v] = cmp_id;
  for (auto u : g[v])
    if (comp[u] == -1)
      dfs2(u);
}

void dfs3(int v) {
  for (auto u : cg[v]) {
    if (h[u] == -1) {
      h[u] = h[v] + 1;
      dfs3(u);
    }
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
  comp.resize(n + 1, -1);

  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to;
    g[from].insert(to);
    g[to].insert(from);
  }

  h[1] = 0;
  dfs(1, -1);

  for (auto [v, u] : br) {
    g[v].erase(u);
    g[u].erase(v);
  }

  for (int i = 1; i <= n; i++)
    if (comp[i] == -1) {
      dfs2(i);
      cmp_id++;
    }

  cg.resize(cmp_id);
  for (auto [u, v] : br) {
    cg[comp[u]].push_back(comp[v]);
    cg[comp[v]].push_back(comp[u]);
  }

  h.assign(cmp_id, -1);
  h[0] = 0;
  dfs3(0);

  int root = max_element(h.begin(), h.end()) - h.begin();
  h.assign(cmp_id, -1);
  h[root] = 0;
  dfs3(root);
  cout << *max_element(h.begin(), h.end());
}