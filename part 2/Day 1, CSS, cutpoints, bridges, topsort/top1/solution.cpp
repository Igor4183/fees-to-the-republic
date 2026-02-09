#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector<set<int>> rg(26), g(26);
vector<int> ord;
vector<int> used(26, 0);

bool dfs(int v, int anc) {
  used[v] = 1;
  for (auto u : g[v]) {
    if (used[u] == 2)
      continue;
    if (used[u] == 1)
      return false;
    if (used[u] == 0)
      if (!dfs(u, v))
        return false;
  }
  used[v] = 2;
  ord.push_back(v);
  return true;
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n;
  vector<string> names(n);
  for (int i = 0; i < n; i++)
    cin >> names[i];

  for (int i = 0; i < n - 1; i++) {
    bool is_round = true;
    for (int k = 0; k < min(names[i].size(), names[i + 1].size()); k++) {
      char from = names[i][k], to = names[i + 1][k];
      if (from != to) {
        is_round = false;
        g[from - 'a'].insert(to - 'a');
        rg[to - 'a'].insert(from - 'a');
        break;
      }
    }
    if (is_round and names[i].size() > names[i + 1].size()) {
      cout << "Impossible";
      return 0;
    }
  }

  for (int i = 0; i < 26; i++) {
    if (used[i] == 0)
      if (!dfs(i, -1)) {
        cout << "Impossible";
        return 0;
      }
  }

  reverse(ord.begin(), ord.end());
  for (auto now : ord)
    cout << (char)(now + 'a');
}
