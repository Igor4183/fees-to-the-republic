#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int INF = 1e18;

int calc_segment(int l, int r, vector<int> &a) {
  if (l > r)
    return 0;
  int m = r - l + 1;
  if (m == 1)
    return INF;
  vector<int> dp(m + 1, INF);
  dp[0] = 0;
  for (int i = 1; i <= m; i++) {
    if (i >= 2) {
      int cost2 = abs(a[l + i - 2] - a[l + i - 1]);
      if (dp[i - 2] < INF)
        dp[i] = min(dp[i], dp[i - 2] + cost2);
    }
    if (i >= 3) {
      int mn = min(a[l + i - 3], min(a[l + i - 2], a[l + i - 1]));
      int mx = max(a[l + i - 3], max(a[l + i - 2], a[l + i - 1]));
      int cost3 = mx - mn;
      if (dp[i - 3] < INF)
        dp[i] = min(dp[i], dp[i - 3] + cost3);
    }
  }
  return dp[m];
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  if (n == 3) {
    int mn = min(a[1], min(a[2], a[3]));
    int mx = max(a[1], max(a[2], a[3]));
    cout << mx - mn << '\n';
    return;
  }

  vector<int> dp_pref(n + 1, INF);
  dp_pref[0] = 0;
  for (int i = 1; i <= n; i++) {
    if (i >= 2) {
      int cost2 = abs(a[i - 1] - a[i]);
      if (dp_pref[i - 2] < INF)
        dp_pref[i] = min(dp_pref[i], dp_pref[i - 2] + cost2);
    }
    if (i >= 3) {
      int mn = min(a[i - 2], min(a[i - 1], a[i]));
      int mx = max(a[i - 2], max(a[i - 1], a[i]));
      int cost3 = mx - mn;
      if (dp_pref[i - 3] < INF)
        dp_pref[i] = min(dp_pref[i], dp_pref[i - 3] + cost3);
    }
  }

  int ans = dp_pref[n];

  if (n >= 4) {
    int costB = abs(a[n] - a[1]) + calc_segment(2, n - 1, a);
    ans = min(ans, costB);
  }
  if (n >= 5) {
    int mnC = min(a[n - 1], min(a[n], a[1]));
    int mxC = max(a[n - 1], max(a[n], a[1]));
    int costC = mxC - mnC + calc_segment(2, n - 2, a);
    ans = min(ans, costC);

    int mnD = min(a[n], min(a[1], a[2]));
    int mxD = max(a[n], max(a[1], a[2]));
    int costD = mxD - mnD + calc_segment(3, n - 1, a);
    ans = min(ans, costD);
  }

  cout << ans << '\n';
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
