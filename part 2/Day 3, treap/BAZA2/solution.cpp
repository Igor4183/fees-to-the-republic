#include <bits/stdc++.h>
#define int int64_t

using namespace std;

mt19937 rng(random_device{}());
const int MOD = 1e18;
const int INF = 1e18;

struct Node {
    Node *l = nullptr, *r = nullptr;
    int x;
    int y = uniform_int_distribution<int>(0, 1e9)(rng);
    int sz = 0;
    int mn = INF;

    Node(int x)
        : x(x), mn(x), sz(1) {
    }
};

Node* root = nullptr;

int Size(Node* v) {
    if (!v) return 0;
    return v->sz;
}

int Mn(Node* v) {
    if (!v) return INF;
    return v->mn;
}

void upd(Node* v) {
    if (!v) return;
    v->mn = min(v->x, min(Mn(v->l), Mn(v->r)));
    v->sz = 1 + Size(v->l) + Size(v->r);
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;

    if (l->y > r->y) {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}

pair<Node*, Node*> split(Node* v, int k) { // (-INF, x) [x, INF)
    if (!v) return {0, 0};

    if (Size(v->l) + 1 <= k) {
        auto p = split(v->r, k - Size(v->l) - 1);
        v->r = p.first;
        upd(v);
        return {v, p.second};
    } else {
        auto p = split(v->l, k);
        v->l = p.second;
        upd(v);
        return {p.first, v};
    }
}

void insert(int idx, int x) {
    auto p = split(root, idx);
    Node* v = new Node(x);
    root = merge(p.first, merge(v, p.second));
}

int getMn(Node* v, int l, int r, int ql, int qr) {
    // cout << !root << ' ' << l << ' ' << r << ' ' << ql << ' ' << qr << endl;
    if (!v or qr <= l or r <= ql) return INF;
    if (ql <= l and r <= qr) return v->mn;

    int mn = INF;
    if (ql <= l + Size(v->l) and l + Size(v->l) < qr) mn = min(mn, v->x);
    if (v->l) mn = min(mn, getMn(v->l, l, l + Size(v->l), ql, qr));
    if (v->r) mn = min(mn, getMn(v->r, l + Size(v->l) + 1, r, ql, qr));
    return mn;
}

void DFS(Node* v, int h = 0) { // for debug
    if (v == nullptr) return;
    DFS(v->l, h + 1);
    cout << Size(v) << ' ' << v->x << ' ' << v->y << '\n';
    DFS(v->r, h + 1);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    set<int> vals;
    int mn = INF, mx = -INF;

    while (n--) {
        char t;
        cin >> t;
        if (t == '+') {
            int i, x;
            cin >> i >> x;
            mn = min(mn, x);
            mx = max(mx, x);
            insert(i, x);
        }
        if (t == '?') {
            int ql, qr;
            cin >> ql >> qr;
            cout << getMn(root, 1, Size(root) + 1, ql, qr + 1) << '\n';
        }
        // DFS(root);
        // cout << endl;
    }
}
