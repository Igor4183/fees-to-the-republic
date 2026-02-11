#include <bits/stdc++.h>
#define int int64_t

using namespace std;

mt19937_64 rng(random_device{}());
const int MOD = 1e9;
const int INF = 1e9 + 1;

struct Node {
    Node *l = nullptr, *r = nullptr;
    int x;
    int y = uniform_int_distribution<int>(0, 1e18)(rng);
    int sum;

    Node(int x)
        : x(x), sum(x) {
    }
};

Node* root = nullptr;

int Sum(Node* v) {
    if (!v) return 0;
    return v->sum;
}

void updSum(Node* v) {
    if (!v) return;
    v->sum = v->x + Sum(v->l) + Sum(v->r);
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;

    if (l->y > r->y) {
        l->r = merge(l->r, r);
        updSum(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        updSum(r);
        return r;
    }
}

pair<Node*, Node*> split(Node* v, int x) { // (-INF, x] (x, INF)
    if (!v) return {0, 0};

    if (x < v->x) {
        auto p = split(v->l, x);
        v->l = p.second;
        updSum(v);
        return {p.first, v};
    } else {
        auto p = split(v->r, x);
        v->r = p.first;
        updSum(v);
        return {v, p.second};
    }
}

void insert(int x) {
    auto p = split(root, x);
    Node* t = new Node(x);
    root = merge(p.first, merge(t, p.second));
}

int getSum(int ql, int qr) {
    if (!root) return 0;
    auto [l, temp] = split(root, ql - 1);
    auto [res, r] = split(temp, qr);
    int ans = 0;
    if (res) ans = res->sum;
    root = merge(l, merge(res, r));
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    unordered_set<int> vals;
    int last = -1;

    while (n--) {
        char t;
        cin >> t;
        if (t == '+') {
            int i;
            cin >> i;
            if (last != -1) i = (i + last) % MOD;
            if (vals.find(i) != vals.end()) {
                last = -1;
                continue;
            }

            vals.insert(i);
            insert(i);
            last = -1;
        }
        if (t == '?') {
            int ql, qr;
            cin >> ql >> qr;
            int sum = getSum(ql, qr);
            cout << sum << '\n';
            last = sum;
        }
    }
}
