#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int MOD = 1e9 + 7;
const int INF = 1e17;
int n;

bool check(int mni, vector<int> &r, vector<int> &x) {
  unordered_map<int, int> m;
  for (int i = 0; i < n; i++)
    m[r[i]]++;

  bool breaked = false;
  vector<int> ans(n);
  m[*min_element(r.begin(), r.end())]--;
  ans[mni] = *min_element(r.begin(), r.end());
  for (int i = mni + 1; i < n; i++) {
    int targ = x[i] - x[i - 1] - ans[i - 1];
    if (m[targ] == 0) {
      breaked = true;
      break;
    }
    m[targ]--;
    ans[i] = targ;
  }
  for (int i = mni - 1; i >= 0; i--) {
    int targ = x[i + 1] - x[i] - ans[i + 1];
    if (m[targ] == 0) {
      breaked = true;
      break;
    }
    m[targ]--;
    ans[i] = targ;
  }
  if (breaked)
    return breaked;

  for (auto now : ans)
    cout << now << ' ';
  return false;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  vector<int> x(n), r(n);
  for (int i = 0; i < n; i++)
    cin >> x[i];
  for (int i = 0; i < n; i++)
    cin >> r[i];

  vector<int> a(n);
  a[0] = 0;
  for (int i = 1; i < n; i++)
    a[i] = x[i] - x[i - 1] - a[i - 1];

  int mn = INF, mni = -1;
  for (int i = 0; i < n; i += 2)
    if (mn > a[i]) {
      mni = i;
      mn = a[i];
    }

  bool temp = check(mni, r, x);
  if (!temp)
    return 0;

  mn = INF;
  for (int i = 1; i < n; i += 2)
    if (mn > a[i]) {
      mni = i;
      mn = a[i];
    }
  temp = check(mni, r, x);
}
