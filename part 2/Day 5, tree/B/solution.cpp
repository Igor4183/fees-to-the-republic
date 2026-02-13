#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int MOD = 1e9 + 7;
const int INF = 1e18;
vector<vector<int>> g;
vector<int> a, dp;
vector<int> ans;

void DFS1(int v = 1, int anc = -1) {
    dp[v] = a[v];
    for (auto to : g[v]) {
        if (to == anc) continue;
        DFS1(to, v);
        dp[v] += max(0LL, dp[to]);
    }
}

void DFS2(int v = 1, int anc = -1) {
    for (auto to : g[v]) {
        if (to == anc) continue;
        dp[v] -= max(dp[to], 0LL);
        dp[to] += max(dp[v], 0LL);
        ans[to] = dp[to];
        DFS2(to, v);
        dp[to] -= max(dp[v], 0LL);
        dp[v] += max(dp[to], 0LL);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    g.resize(n + 1);
    a.resize(n + 1);
    dp.resize(n + 1, 0);
    ans.resize(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 0) a[i] = -1;
    }

    for (int i = 0; i < n - 1; i++) {
        int from, to;
        cin >> from >> to;
        g[from].push_back(to);
        g[to].push_back(from);
    }

    DFS1();
    ans[1] = dp[1];
    DFS2();

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
}