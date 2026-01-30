#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int MOD = 1e9 + 7;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, x;
  cin >> n >> x;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];

  vector<int> L(n, -1), R(n, n);
  stack<pair<int, int>> now;
  vector<int> pref(n + 1);
  pref[0] = 0;

  for (int i = 0; i < n; i++)
    pref[i + 1] = pref[i] + b[i];

  for (int i = 0; i < n; i++) {
    while (!now.empty() and a[i] < now.top().first) {
      R[now.top().second] = i;
      now.pop();
    }
    now.push({a[i], i});
  }

  while (!now.empty())
    now.pop();
  for (int i = n - 1; i >= 0; i--) {
    while (!now.empty() and a[i] <= now.top().first) {
      L[now.top().second] = i;
      now.pop();
    }
    now.push({a[i], i});
  }

  int res = 0;
  for (int i = 0; i < n; i++) {
    if (i - L[i] < R[i] - i) {
      for (int j = L[i] + 1; j <= i; j++) {
        int lsum = pref[i] - pref[j];
        int l = i, r = R[i] - 1;
        while (l < r) {
          int m = (l + r + 1) / 2;
          int rsum = pref[m + 1] - pref[i];
          if (lsum + rsum + a[i] <= x)
            l = m;
          else
            r = m - 1;
        }
        if ((pref[l + 1] - pref[j]) + a[i] <= x)
          res += (l - i + 1);
      }
    } else {
      for (int j = R[i] - 1; j >= i; j--) {
        int rsum = pref[j + 1] - pref[i];
        int l = L[i] + 1, r = i;
        while (l < r) {
          int m = (l + r) / 2;
          int lsum = pref[i] - pref[m];
          if (lsum + rsum + a[i] <= x)
            r = m;
          else
            l = m + 1;
        }
        if ((pref[j + 1] - pref[l]) + a[i] <= x)
          res += (i - l + 1);
      }
    }
  }

  cout << res;
}