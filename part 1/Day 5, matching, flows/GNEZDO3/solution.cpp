#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int INF = 1e18;

vector<vector<char>> g;
const vector<int> dx{-1, 1, 0, 0}, dy{0, 0, -1, 1};
vector<vector<pair<int, int>>> mt;
vector<vector<bool>> used;
int n, m;

bool try_kuhn(int x, int y) {
  if (used[x][y])
    return false;
  used[x][y] = true;

  for (int k = 0; k < 4; k++) {
    int i = x + dx[k], j = y + dy[k];
    if (i >= 0 and i < n and j >= 0 and j < m and g[i][j] == '.' and
        !used[i][j]) {
      if (mt[i][j] == make_pair(-1, -1) or
          try_kuhn(mt[i][j].first, mt[i][j].second)) {
        mt[i][j] = {x, y};
        return true;
      }
    }
  }
  return false;
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  g.resize(n, vector<char>(m));
  mt.resize(n, vector<pair<int, int>>(m, {-1, -1}));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> g[i][j];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == '#')
        continue;
      used.assign(n, vector<bool>(m, 0));
      try_kuhn(i, j);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] != '#' and mt[i][j] == make_pair(-1, -1)) {
        cout << "No";
        return 0;
      }
    }
  }
  cout << "Yes";
}
