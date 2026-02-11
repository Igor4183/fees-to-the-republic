#include <bits/stdc++.h>
#define int int64_t

using namespace std;

const int MAX = 1e9;

struct Node {
    int l = -MAX, r = MAX;
};

vector<Node> tree;

Node unite(const Node& v1, const Node& v2) {
    return {max(v1.l, v2.l), min(v1.r, v2.r)};
}

void update(int v, int l, int r, int idx, Node val) {
    if (idx < l or r <= idx) return;
    if (r - l == 1) {
        tree[v] = val;
        return;
    }
    int m = (l + r) / 2;
    update(v * 2 + 1, l, m, idx, val);
    update(v * 2 + 2, m, r, idx, val);
    tree[v] = unite(tree[v * 2 + 1], tree[v * 2 + 2]);
}

Node getSub(int v, int l, int r, int ql, int qr) {
    if (qr <= l or r <= ql) return Node();
    if (ql <= l and r <= qr) return tree[v];
    int m = (l + r) / 2;
    Node v1 = getSub(v * 2 + 1, l, m, ql, qr), v2 = getSub(v * 2 + 2, m, r, ql, qr);
    return unite(v1, v2);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    tree.resize(4 * n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        update(0, 0, n, i, Node{l, r});
    }
    while (q--) {
        char t;
        cin >> t;
        if (t == '?') {
            int ql, qr;
            cin >> ql >> qr;
            Node res = getSub(0, 0, n, ql - 1, qr);
            cout << max(0LL, res.r - res.l + 1) << '\n';
        } else {
            int idx, a, b;
            cin >> idx >> a >> b;
            update(0, 0, n, idx - 1, Node{a, b});
        }
    }
}
