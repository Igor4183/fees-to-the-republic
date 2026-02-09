#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> rg(n + 1);
    vector<int> deg(n + 1);

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        rg[to].push_back(from);
        deg[from]++;
    }

    priority_queue<int, vector<int>> pq;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            pq.push(i);

    vector<int> ord;
    while (!pq.empty()) {
        int v = pq.top();
        pq.pop();
        ord.emplace_back(v);
        for (auto u : rg[v])
            if (--deg[u] == 0)
                pq.push(u);
    }
    reverse(ord.begin(), ord.end());

    vector<int> ans(n + 1, 0);
    for (int i = 0; i < n; i++)
        ans[ord[i]] = i + 1;
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
}