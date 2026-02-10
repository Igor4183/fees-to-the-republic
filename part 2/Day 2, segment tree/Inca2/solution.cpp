#include <bits/stdc++.h>
#define int int64_t

using namespace std;

vector<int> cords;
unordered_map<int, int> compr;

int n, d;
vector<int> h;
vector<pair<int, int>> tree;

void update(int v, int l, int r, int idx, pair<int, int> val) { // val = {mxcnt, i}
    if (idx < l or r <= idx) return;
    if (r - l == 1) {
        if (tree[v].first < val.first) tree[v] = val;
        return;
    }

    int m = (l + r) / 2;
    update(v * 2 + 1, l, m, idx, val);
    update(v * 2 + 2, m, r, idx, val);
    tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
}

pair<int, int> getMax(int v, int l, int r, int ql, int qr) {
    if (qr <= l or r <= ql) return {0, -1};
    if (ql <= l and r <= qr) return tree[v];

    int m = (l + r) / 2;
    return max(getMax(v * 2 + 1, l, m, ql, qr), getMax(v * 2 + 2, m, r, ql, qr));
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> d;
    cords.resize(n);
    h.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        cords[i] = h[i];
    }

    sort(cords.begin(), cords.end());
    cords.resize(unique(cords.begin(), cords.end()) - cords.begin());
    const int sz = cords.size();
    for (int i = 0; i < sz; i++) compr[cords[i]] = i;

    tree.resize(4 * sz, {0, -1});
    vector<int> prev(n), mx(n);

    for (int i = 0; i < n; i++) {
        int ql = upper_bound(cords.begin(), cords.end(), h[i] - d) - cords.begin();
        int qr = lower_bound(cords.begin(), cords.end(), h[i] + d) - cords.begin();
        // cout << i << ' ' << h[i] << ": " << ql << ' ' << qr << ' ' << getMax(0, 0, sz, 0, ql).first << ' ' << getMax(0, 0, sz, qr, sz).first << endl;
        pair<int, int> ans = max(getMax(0, 0, sz, 0, ql), getMax(0, 0, sz, qr, sz));
        mx[i] = ans.first + 1;
        prev[i] = ans.second;
        update(0, 0, sz, compr[h[i]], make_pair(mx[i], i));
    }

    // for (auto now : mx) cout << setw(3) << now;
    // cout << endl;
    // for (auto now : prev) cout << setw(3) << now;
    // cout << endl;

    int ptr = tree[0].second;
    vector<int> ans;
    while (ptr != -1) {
        ans.push_back(ptr);
        ptr = prev[ptr];
    }
    reverse(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (auto now : ans) cout << now + 1 << ' ';
}
