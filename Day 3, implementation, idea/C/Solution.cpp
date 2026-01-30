#include <bits/stdc++.h>
#define int int64_t

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> bil(n);
  vector<int> c(m);
  for (int i = 0; i < n; i++)
    cin >> bil[i].first;
  for (int i = 0; i < n; i++)
    cin >> bil[i].second;
  for (int i = 0; i < m; i++)
    cin >> c[i];

  sort(c.begin(), c.end());
  sort(bil.begin(), bil.end(), greater<pair<int, int>>());
  int val = bil[0].first, idx = 0;
  for (int i = 1; i < n; i++)
    if (val > bil[i].second) {
      val = bil[i].first;
      idx = i;
    }

  int cnt = upper_bound(c.begin(), c.end(), val) - c.begin();
  cnt += n - idx;
  cout << (cnt % 2 == 1 ? "First" : "Second");
}
