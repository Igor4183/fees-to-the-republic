#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int INF = 1e18;

vector<vector<int>> g;
vector<int> mt, used;

bool try_kuhn(int v) {
  if (used[v])
    return false;
  used[v] = true;

  for (auto to : g[v]) {
    if (mt[to] == -1 or try_kuhn(mt[to])) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  g.resize(n + 1);
  mt.resize(n + 1, -1);

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g[a].emplace_back(b);
  }

  for (int v = 1; v <= n; v++) {
    // if (mt[v]!=-1) continue;
    used.assign(n + 1, false);
    try_kuhn(v);
    // cout << v << ": ";
    // for (int i = 1; i<=n; i++) cout << mt[i] << ' ';
    // cout << endl;
  }

  int cnt = 0;
  for (int i = 1; i <= n; i++)
    cnt += (mt[i] == -1);
  cout << cnt;
}
