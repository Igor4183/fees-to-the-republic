#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int MOD = 1e9 + 7;

struct Tree {
  vector<int> g;
  int n;

  Tree(int sz) : n(sz) { g.resize(4 * sz); }

  void add(int v, int l, int r, int idx, int val) {
    if (idx < l or r <= idx)
      return;
    if (r - l == 1) {
      g[v] += val;
      return;
    }

    int m = (l + r) / 2;
    add(v * 2 + 1, l, m, idx, val);
    add(v * 2 + 2, m, r, idx, val);
    g[v] = g[v * 2 + 1] + g[v * 2 + 2];
  }

  int getSum(int v, int l, int r, int ql, int qr) {
    if (qr <= l or r <= ql)
      return 0;
    if (ql <= l and r <= qr)
      return g[v];

    int m = (l + r) / 2;
    return (getSum(v * 2 + 1, l, m, ql, qr) + getSum(v * 2 + 2, m, r, ql, qr)) %
           MOD;
  }
};

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, ans = 0;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  map<int, int> comp;
  vector<int> sorted = a;
  sort(sorted.begin(), sorted.end());
  sorted.resize(unique(sorted.begin(), sorted.end()) - sorted.begin());
  const int sz = sorted.size();
  for (int i = 0; i < sz; i++)
    comp[sorted[i]] = i;

  Tree l(sz), r(sz);
  for (int i = 1; i <= n; i++)
    r.add(0, 0, sz, comp[a[i - 1]], (n - i + 1));
  for (int i = 1; i <= n; i++) {
    l.add(0, 0, sz, comp[a[i - 1]], i);
    r.add(0, 0, sz, comp[a[i - 1]], -(n - i + 1));

    int tl = (n - i + 1) * l.getSum(0, 0, sz, 0, comp[a[i - 1]]) % MOD;
    int tr = i * r.getSum(0, 0, sz, 0, comp[a[i - 1]]) % MOD;
    ans = (ans + a[i - 1] * (tl + tr)) % MOD;
  }

  for (int i = 1; i <= n; i++)
    ans = (ans + (a[i - 1] * i % MOD) * (n - i + 1)) % MOD;
  cout << ans;
}
