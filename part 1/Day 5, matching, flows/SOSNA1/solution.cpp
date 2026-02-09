#include <bits/stdc++.h>
#define int int64_t
using namespace std;

struct Edge {
  int a, b, cap, flow;
};
int n, m, s, t;
const int INF = 1e17;
vector<vector<int>> g;
vector<Edge> e;
vector<int> d, ptr;

void add_edge(int a, int b, int cap) {
  Edge e1 = {a, b, cap, 0};
  Edge e2 = {b, a, 0, 0};
  g[a].push_back(e.size());
  e.push_back(e1);
  g[b].push_back(e.size());
  e.push_back(e2);
}

bool BFS() {
  d.assign(n + 1, -1);
  queue<int> q;
  q.push(s);
  d[s] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (auto id : g[v]) {
      int to = e[id].b;
      if (d[to] == -1 and e[id].cap > e[id].flow) {
        q.push(to);
        d[to] = d[v] + 1;
      }
    }
  }
  return d[t] != -1;
}

int DFS(int v, int flow) {
  if (flow == 0)
    return 0;
  if (v == t)
    return flow;

  for (; ptr[v] < g[v].size(); ptr[v]++) {
    int id = g[v][ptr[v]], to = e[id].b;
    if (d[to] != d[v] + 1)
      continue;
    int pushed = DFS(to, min(flow, e[id].cap - e[id].flow));
    if (pushed != 0) {
      e[id].flow += pushed;
      e[id + 1].flow -= pushed;
      return pushed;
    }
  }
  return 0;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  s = 1;
  t = n;
  g.resize(n + 1);
  e.reserve(2 * m);
  for (int i = 0; i < m; i++) {
    int a, b, cap;
    cin >> a >> b >> cap;
    add_edge(a, b, cap);
  }

  int ans = 0;
  while (BFS()) {
    ptr.assign(n + 1, 0);
    while (int pushed = DFS(s, INF))
      ans += pushed;
  }
  cout << ans;
}
