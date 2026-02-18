#include <bits/stdc++.h>

#define int int64_t

using namespace std;

struct Query {
    int l, r, idx;
};

const int MOD = 1e9 + 7;
const int MAXN = 5e5 + 10;
const int MAXA = 2e5 + 10;
vector<int> tree, at;

int binpow(int val, int deg) { /// O(log val)
    int res = 1;
    while (deg) {
        if (deg & 1) res *= val;
        val *= val;
        deg >>= 1;
        if (res >= MOD) res %= MOD;
        if (val >= MOD) val %= MOD;
    }
    return res;
}

void update(int v, int l, int r, int idx) {
    if (idx < l or r <= idx) return;
    if (r - l == 1) {
        tree[v] = at[idx];
        return;
    }
    int m = (l + r) / 2;
    update(v * 2 + 1, l, m, idx);
    update(v * 2 + 2, m, r, idx);
    tree[v] = tree[v * 2 + 1] * tree[v * 2 + 2];
    if (tree[v] >= MOD) tree[v] %= MOD;
}

int query(int v, int l, int r, int ql, int qr) {
    if (qr <= l or r <= ql) return 1;
    if (ql <= l and r <= qr) return tree[v];
    int m = (l + r) / 2;
    return query(v * 2 + 1, l, m, ql, qr) * query(v * 2 + 2, m, r, ql, qr) % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<Query> querys(m);
    vector<int> freq(MAXA), rec(MAXA);

    for (int i = 0; i < n; i++) cin >> a[i];

    iota(freq.begin(), freq.end(), 0);
    for (int i = 2; i * i < MAXA; i++) { /// O(n*loglog(maxA))
        if (freq[i] == i) {
            for (int j = i * i; j < MAXA; j += i) freq[j] = i;
        }
    }

    for (int i = 1; i < MAXA; i++) /// O(maxA*log(MOD-2))=O(30*maxA)
        rec[i] = binpow(i, MOD - 2);

    vector<vector<int>> rad(n);
    for (int i = 0; i < n; i++) { /// O(n*log(maxA))
        int val = a[i];
        while (val != 1) {
            rad[i].emplace_back(freq[val]);
            val /= freq[val];
        }
        rad[i].resize(unique(rad[i].begin(), rad[i].end()) - rad[i].begin());
    }

    for (int i = 0; i < m; i++) {
        int ql, qr;
        cin >> ql >> qr;
        querys[i] = {ql - 1, qr - 1, i};
    }
    sort(querys.begin(), querys.end(), [](const Query& f, const Query& s) {
        return f.r < s.r;
    });

    vector<int> ans(m);
    vector<int> last(MAXA, -1);
    tree.resize(4 * n, 1);
    at.resize(n, 1);
    int r = -1;
    for (const auto q : querys) { // O(n*log(n))
        while (r < q.r) {
            r++;
            for (const auto val : rad[r]) {
                if (last[val] != -1) {
                    at[last[val]] *= rec[val];
                    if (at[last[val]] >= MOD) at[last[val]] %= MOD;
                    update(0, 0, n, last[val]);
                }
                last[val] = r;
                at[r] *= val;
                if (at[r] >= MOD) at[r] %= MOD;
                update(0, 0, n, r);
            }
        }
        // cout << q.idx << ": ";
        // for (auto now : tree) cout << now << ' ';
        // cout << endl;
        ans[q.idx] = query(0, 0, n, q.l, q.r + 1);
    }

    for (int i = 0; i < m; i++) cout << ans[i] << '\n';
}
