#include <bits/stdc++.h>
#define int int64_t
#define ld long double

using namespace std;

const int MOD = 1e9 + 7;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  int suf = n;
  while (suf > 0 and a[suf - 1] == suf)
    suf--;
  ld res = 0;
  if (suf == 0)
    res = 1;

  while (m--) {
    int r;
    ld p;
    cin >> r >> p;
    if (r >= suf)
      res += (1 - res) * p;
  }
  cout << fixed << setprecision(6) << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
