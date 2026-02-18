#include <bits/stdc++.h>
#define int int64_t

using namespace std;

struct Node {
    int mxc = 0;
    int sum = 0;
    unordered_map<int, int> cnt;
};

vector<int> c;
vector<vector<int>> g;
vector<int> ans;
vector<Node> tree;

void DFS(int v = 1, int anc = -1) {
    for (auto u : g[v]) {
        if (u == anc) continue;
        DFS(u, v);

        if (tree[u].cnt.size() > tree[v].cnt.size())
            swap(tree[u], tree[v]);

        for (auto p : tree[u].cnt) {
            tree[v].cnt[p.first] += p.second;
            if (tree[v].cnt[p.first] == tree[v].mxc)
                tree[v].sum += p.first;
            else if (tree[v].cnt[p.first] > tree[v].mxc) {
                tree[v].mxc = tree[v].cnt[p.first];
                tree[v].sum = p.first;
            }
        }
    }

    tree[v].cnt[c[v]]++;
    if (tree[v].cnt[c[v]] == tree[v].mxc)
        tree[v].sum += c[v];
    else if (tree[v].cnt[c[v]] > tree[v].mxc) {
        tree[v].mxc = tree[v].cnt[c[v]];
        tree[v].sum = c[v];
    }

    ans[v] = tree[v].sum;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    int n;
    cin >> n;
    c.resize(n + 1);
    g.resize(n + 1);
    ans.resize(n + 1, 0);
    tree.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];

    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        g[v].emplace_back(u);
        g[u].emplace_back(v);
    }

    DFS();

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
}
