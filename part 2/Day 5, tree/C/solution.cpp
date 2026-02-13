#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int MOD = 1e9 + 7;
const int INF = 1e18;
vector<vector<int>> g;
vector<int> dp, sum;
int ans = 0;

void DFS1(int v = 1, int anc = -1) {
    dp[v] = 0;
    sum[v] = 1;
    for (auto to : g[v]) {
        if (to == anc) continue;
        DFS1(to, v);
        sum[v] += sum[to];
        dp[v] += dp[to];
    }
    dp[v] += sum[v];
}

void DFS2(int v = 1, int anc = -1) {
    for (auto to : g[v]) {
        if (to == anc) continue;
        dp[v] -= dp[to] + sum[to];
        sum[v] -= sum[to];

        sum[to] += sum[v];
        dp[to] += dp[v] + sum[v];
        ans = max(ans, dp[to]);
        DFS2(to, v);
        dp[to] -= dp[v] + sum[v];
        sum[to] -= sum[v];

        sum[v] += sum[to];
        dp[v] += dp[to] + sum[to];
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    g.resize(n + 1);
    sum.resize(n + 1);
    dp.resize(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int from, to;
        cin >> from >> to;
        g[from].emplace_back(to);
        g[to].emplace_back(from);
    }

    DFS1();
    ans = dp[1];
    DFS2();
    cout << ans;
}