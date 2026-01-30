#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  string a, b;
  cin >> n >> a >> b;
  vector<int> ans;

  for (int i = 0; i < n - 1; i++)
    if (a[i] != a[i + 1])
      ans.push_back(i);
  if (a[n - 1] == '1')
    ans.push_back(n - 1);

  int now = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (now != b[i] - '0') {
      ans.push_back(i);
      now = 1 - now;
    }
  }
  cout << ans.size() << ' ';
  for (auto now : ans)
    cout << now + 1 << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--)
    solve();
}
