#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int MOD = 1e9 + 7;
const int INF = 1e18;
vector<vector<int>> g;
vector<int> p, s, a;

void DFS(int v, int sum = 0) {
    if (a[v] != -1)
        sum += a[v];
    else {
        a[v] = s[v] - sum;
        sum = s[v];
    }
    for (auto to : g[v]) DFS(to, sum);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    g.resize(n + 1);
    p.resize(n + 1);
    s.resize(n + 1);
    a.resize(n + 1, -1);
    p[1] = -1;
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        g[p[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> s[i];

    for (int v = 2; v <= n; v++) {
        if (s[v] != -1) continue;
        int mn = INF;
        for (auto to : g[v]) mn = min(mn, s[to]);
        if (mn == INF) {
            a[v] = 0;
            continue;
        }
        a[v] = mn - s[p[v]];
        if (a[v] < 0) {
            cout << -1;
            return 0;
        }
    }
    DFS(1);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] < 0) {
            cout << -1;
            return 0;
        }
        sum += a[i];
    }
    cout << sum;
}