#include <bits/stdc++.h>
#define int int64_t

using namespace std;

struct Query {
    int l, r, x, idx;
};

vector<bool> ans;
vector<int> tree;
vector<int> p;
vector<Query> Q;
vector<vector<int>> g;
vector<int> tin, tout;
int timer;

void add(int v, int l, int r, int idx, int val) {
    if (idx < l or r <= idx) return;
    if (r - l == 1) {
        tree[v] = val;
        return;
    }
    int m = (l + r) / 2;
    add(v * 2 + 1, l, m, idx, val);
    add(v * 2 + 2, m, r, idx, val);
    tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
}

int get_max(int v, int l, int r, int ql, int qr) {
    if (qr <= l or r <= ql) return 0;
    if (ql <= l and r <= qr) return tree[v];

    int m = (l + r) / 2;
    int v1 = get_max(v * 2 + 1, l, m, ql, qr), v2 = get_max(v * 2 + 2, m, r, ql, qr);
    return max(v1, v2);
}

void DFS(int v = 1, int anc = -1) {
    tin[v] = timer++;
    for (auto u : g[v])
        if (u != anc) DFS(u, v);
    tout[v] = timer++;
}

void solve() {
    timer = 1;
    int n, q;
    cin >> n >> q;
    g.assign(n + 1, {});
    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    p.assign(n + 1, 0);
    ans.assign(q, 0);
    Q.assign(q, {});
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        g[v].emplace_back(u);
        g[u].emplace_back(v);
    }
    for (int i = 1; i <= n; i++) cin >> p[i];

    DFS();
    tree.assign(4 * timer, 0);

    for (int i = 0; i < q; i++) {
        cin >> Q[i].l >> Q[i].r >> Q[i].x;
        Q[i].idx = i;
    }
    sort(Q.begin(), Q.end(), [](const Query& a, const Query& b) {
        return a.r < b.r;
    });

    int r = 0;
    for (int i = 0; i < q; i++) {
        while (r < Q[i].r) {
            r++;
            // cout << "add " << timer << ' ' << tin[p[r]] << ' ' << r << endl;
            add(0, 0, timer, tin[p[r]], r);
        }
        // cout << "get_max " << timer << ' ' << tin[Q[i].x] << ' ' << tout[Q[i].x] << endl;
        int mx = get_max(0, 0, timer, tin[Q[i].x], tout[Q[i].x]);
        if (mx >= Q[i].l) ans[Q[i].idx] = 1;
    }

    for (auto now : ans) cout << (now ? "YES\n" : "NO\n");
    cout << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
