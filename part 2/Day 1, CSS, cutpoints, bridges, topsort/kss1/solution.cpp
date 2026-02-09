#include <bits/stdc++.h>
#define int int64_t
using namespace std;

vector<vector<int>> g, rg;
vector<unordered_set<int>> cg;
vector<int> used, ord;
int cmp_id = 0;

void dfs(int v) {
  used[v] = true;
  for (auto u : g[v]) {
    if (!used[u])
      dfs(u);
  }
  ord.push_back(v);
}

void dfs2(int v) {
  used[v] = cmp_id;
  for (auto u : rg[v])
    if (used[u] == 0)
      dfs2(u);
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("condense2.in", "r", stdin);
  freopen("condense2.out", "w", stdout);

  int n, m;
  cin >> n >> m;

  g.resize(n + 1);
  rg.resize(n + 1);
  used.resize(n + 1, 0);

  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to;
    g[from].push_back(to);
    rg[to].push_back(from);
  }

  for (int i = 1; i <= n; i++)
    if (!used[i])
      dfs(i);
  used.assign(n + 1, 0);
  reverse(ord.begin(), ord.end());

  for (auto v : ord)
    if (!used[v]) {
      cmp_id++;
      dfs2(v);
    }

  cg.resize(cmp_id + 1);
  for (int v = 1; v <= n; v++) {
    for (auto u : g[v])
      if (used[u] != used[v])
        cg[used[v]].insert(used[u]);
  }

  int cnt = 0;
  for (int i = 1; i <= cmp_id; i++)
    cnt += cg[i].size();
  cout << cnt;
}
