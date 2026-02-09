#include <bits/stdc++.h>
#define int int32_t
using namespace std;

vector<vector<int>> g;
vector<int> tin;
vector<int> mt;
int timer = 1;

bool try_kuhn(int v) {
  if (tin[v] == timer)
    return false;
  tin[v] = timer;

  for (auto to : g[v])
    if (mt[to] == -1) {
      mt[to] = v;
      return true;
    }
  for (auto to : g[v])
    if (try_kuhn(mt[to])) {
      mt[to] = v;
      return true;
    }
  return false;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  mt.resize(n, -1);
  vector<int> compr(2 * n), l(2 * n);
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    compr[i * 2] = a;
    compr[i * 2 + 1] = b;
    l[i * 2] = a;
    l[i * 2 + 1] = b;
  }

  sort(compr.begin(), compr.end());
  compr.resize(unique(compr.begin(), compr.end()) - compr.begin());
  const int m = compr.size();

  vector<int> U(n), V(n);
  g.resize(m);
  for (int i = 0; i < n; ++i) {
    g[lower_bound(compr.begin(), compr.end(), l[2 * i]) - compr.begin()]
        .emplace_back(i);
    g[lower_bound(compr.begin(), compr.end(), l[2 * i + 1]) - compr.begin()]
        .emplace_back(i);
  }

  int cnt = 0;
  tin.resize(m, 0);
  for (int i = 0; i < m; i++) {
    cnt += try_kuhn(i);
    timer++;

    if (cnt == n) {
      cout << compr[i];
      return 0;
    }
  }
  cout << -1;
}
