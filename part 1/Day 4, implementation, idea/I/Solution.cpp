#include <bits/stdc++.h>
#define int int64_t

using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string str;
  cin >> str;
  bool first = true;
  for (auto &c : str) {
    if (first and c == '9') {
      first = false;
      continue;
    }
    if (c >= '5')
      c = 9 - (c - '0') + '0';
    first = false;
  }
  cout << str;
}
