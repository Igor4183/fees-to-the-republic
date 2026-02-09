#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int INF = 1e18;

int n, m;
vector<int> x;
vector<vector<int>> cost;
vector<int> dp_prev, dp_cur;

void solve_dc(int l, int r, int optL, int optR) {
  if (l > r)
    return;
  int mid = (l + r) >> 1;
  int bestOpt = optL;
  dp_cur[mid] = INF;
  int end = min(mid, optR);
  for (int i = optL; i <= end; i++) {
    int cand = dp_prev[i - 1];
    if (cand >= INF)
      continue;
    cand += cost[i][mid];
    if (cand < dp_cur[mid]) {
      dp_cur[mid] = cand;
      bestOpt = i;
    }
  }
  solve_dc(l, mid - 1, optL, bestOpt);
  solve_dc(mid + 1, r, bestOpt, optR);
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  x.resize(n + 1, 0);
  cost.resize(n + 1, vector<int>(n + 1, 0));

  for (int i = 1; i <= n; ++i)
    cin >> x[i];
  sort(x.begin() + 1, x.end());
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      int d = x[j] - x[i];
      cost[i][j] = d * d;
    }
  }

  dp_prev.resize(n + 1, INF);
  dp_cur.resize(n + 1, INF);
  dp_prev[0] = 0;

  for (int k = 1; k <= m; k++) {
    for (int i = 0; i <= n; i++)
      dp_cur[i] = INF;
    solve_dc(1, n, 1, n);
    dp_prev.swap(dp_cur);
  }

  cout << dp_prev[n];
}
