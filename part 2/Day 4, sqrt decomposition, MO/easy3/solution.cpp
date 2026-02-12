#include <bits/stdc++.h>
#define ll int64_t
#define int int32_t
#define bool int8_t

using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<pair<int, int>> adj(m);

    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        g[v].emplace_back(u);
        g[u].emplace_back(v);
        adj[i] = {v, u};
    }
    vector<int> deg(n + 1);
    for (int i = 1; i <= n; i++) deg[i] = g[i].size();
    for (auto& [l, r] : adj)
        if (deg[l] < deg[r]) swap(l, r);

    sort(adj.begin(), adj.end(), [&](const auto& a, const auto& b) {
        return deg[a.first] > deg[b.first];
    });
    int last = -1;
    ll ans = 0;
    vector<int> mark(n + 1, 0);
    for (const auto& [v, u] : adj) {
        if (last != v) {
            last = v;
            for (auto w : g[v]) mark[w] = v;
        }
        int cnt = 0;
        for (auto w : g[u]) cnt += (mark[w] == v);
        ans += 1LL * cnt * (cnt - 1) / 2;
    }

    cout << ans;
}