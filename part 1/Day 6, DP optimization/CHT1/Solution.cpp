#include <bits/stdc++.h>
#define int int64_t
#define ld long double

using namespace std;

const int INF = 1e18;

struct line {
  int k, b;
};

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<line> f(n);
  for (int i = 0; i < n; i++) {
    int k, b;
    cin >> k >> b;
    f[i] = {k, b};
  }

  sort(f.begin(), f.end(), [](const line &a, const line &b) {
    if (a.k == b.k)
      return a.b < b.b;
    return a.k > b.k;
  });
  f.resize(unique(f.begin(), f.end(),
                  [](const line &a, const line &b) {
                    return a.k == b.k and a.b == b.b;
                  }) -
           f.begin());

  vector<pair<int, ld>> sub;
  sub.emplace_back(0, -INF);

  for (int i = 1; i < n; i++) {
    auto &[ki, bi] = f[i];
    while (!sub.empty()) {
      auto &[k, b] = f[sub.back().first];
      if (k == ki) {
        if (bi < b) {
          sub.pop_back();
          continue;
        } else
          break;
      }
      ld x = ((ld)bi - b) / ((ld)k - ki);

      if (x < sub.back().second) {
        sub.pop_back();
      } else {
        sub.emplace_back(i, x);
        break;
      }
    }
  }

  vector<ld> cord;
  for (auto [idxl, x] : sub) {
    cord.push_back(x);
  }

  while (q--) {
    int x;
    cin >> x;
    int idxsub = upper_bound(cord.begin(), cord.end(), x) - cord.begin() - 1;
    int idxf = sub[idxsub].first;
    cout << f[idxf].k * x + f[idxf].b << '\n';
  }
}