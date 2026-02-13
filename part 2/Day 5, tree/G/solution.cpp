#include <bits/stdc++.h>
#define int int64_t

using namespace std;

string str;
vector<vector<int>> g;
vector<vector<pair<int, int>>> order; /// {tin, A}
vector<int> tin, tout;
vector<int> h;
int timer = 1;

void DFS(int v, int hv = 1) {
    tin[v] = timer++;
    h[v] = hv;
    order[hv].emplace_back(tin[v], order[hv].back().second ^ (1LL << (str[v] - 'a')));
    for (auto u : g[v])
        DFS(u, h[v] + 1);
    tout[v] = timer++;
}

void solve() {
    int v, hi;
    cin >> v >> hi;

    if (hi <= h[v]) {
        cout << "Yes\n";
        return;
    }

    int l = lower_bound(order[hi].begin(), order[hi].end(), make_pair(tin[v], 0LL)) - order[hi].begin() - 1;
    int r = lower_bound(order[hi].begin(), order[hi].end(), make_pair(tout[v], 0LL)) - order[hi].begin() - 1;

    int val = order[hi][l].second ^ order[hi][r].second;
    if (val - (val & -val) == 0)
        cout << "Yes\n";
    else
        cout << "No\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    g.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    cin >> str;
    str = " " + str;
    order.resize(n + 1, vector<pair<int, int>>(1, make_pair(-1, 0)));
    h.resize(n + 1);
    tin.resize(n + 1);
    tout.resize(n + 1);
    DFS(1);

    while (q--) solve();
}
