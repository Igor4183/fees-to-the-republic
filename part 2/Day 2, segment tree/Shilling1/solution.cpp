#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int INF = 1e6;
vector<int> tree;
vector<int> a;

void build(int v, int l, int r) {
    if (r - l == 1) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m, r);
    tree[v] = min(tree[v * 2 + 1], tree[v * 2 + 2]);
}

void update(int v, int l, int r, int idx) {
    if (idx < l or r <= idx) return;
    if (r - l == 1) {
        tree[v] = INF;
        return;
    }
    int m = (l + r) / 2;
    update(v * 2 + 1, l, m, idx);
    update(v * 2 + 2, m, r, idx);
    tree[v] = min(tree[v * 2 + 1], tree[v * 2 + 2]);
}

int getMn(int v, int l, int r, int ql, int qr) {
    if (qr <= l or r <= ql) return INF;
    if (ql <= l and r <= qr) return tree[v];
    int m = (l + r) / 2;
    return min(getMn(v * 2 + 1, l, m, ql, qr), getMn(v * 2 + 2, m, r, ql, qr));
}

void solve() {
    int n;
    cin >> n;
    a.resize(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    tree.resize(4 * n);
    build(0, 0, n);
    vector<queue<int>> vq(n + 1);
    for (int i = 0; i < n; i++)
        vq[a[i]].push(i);

    for (int i = 0; i < n; i++) {
        if (vq[b[i]].empty()) {
            cout << "NO\n";
            return;
        }
        int idx = vq[b[i]].front();
        vq[b[i]].pop();

        if (getMn(0, 0, n, 0, idx) < b[i]) {
            // cout << i << ' ' << idx << '\n';
            cout << "NO\n";
            return;
        }
        update(0, 0, n, idx);
    }
    cout << "YES\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
