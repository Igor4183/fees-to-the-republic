#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  int mxbit = 63 - __builtin_clzll(n);
  int res = 0;
  vector<bool> idxs(n, true);
  vector<bool> vals(n + 1, true);

  for (int i = 0; i <= mxbit; i++) {
    int num = (1 << i);
    int c0 = 0, c1 = 0;
    for (int j = 1; j <= n; j++) {
      if (!vals[j])
        continue;
      ((j & num) ? c1++ : c0++);
    }

    vector<vector<int>> r(2);
    for (int j = 1; j < n; j++) {
      if (!idxs[j])
        continue;
      cout << "? " << j << ' ' << num << '\n';
      cout.flush();
      int res;
      cin >> res;
      r[res].push_back(j);
    }
    if (c0 != r[0].size()) {
      for (auto idx : r[1])
        idxs[idx] = false;
      for (int j = 1; j <= n; j++)
        if (j & num)
          vals[j] = false;
    } else {
      res |= num;
      for (auto idx : r[0])
        idxs[idx] = false;
      for (int j = 1; j <= n; j++)
        if (!(j & num))
          vals[j] = false;
    }
  }
  cout << "! " << res << '\n';
  cout.flush();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
}
