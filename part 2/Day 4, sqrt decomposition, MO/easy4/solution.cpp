#include <bits/stdc++.h>
#define int int64_t

using namespace std;

struct Query {
    int l, r, idx;
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    const int c = sqrt(n);
    vector<int> a(n), ans(m);
    vector<vector<Query>> qs((n + c - 1) / c);

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        qs[l / c].push_back({l, r, i});
    }

    for (int i = 0; i < qs.size(); i++) {
        sort(qs[i].begin(), qs[i].end(), [](const Query& f, const Query& s) {
            return f.r < s.r;
        });

        int l = i * c, r = i * c - 1;
        int cnt = 0;
        unordered_map<int, int> um;

        for (const Query& q : qs[i]) {
            while (r < q.r) {
                r++;
                if (um[a[r]] == a[r]) cnt--;
                um[a[r]]++;
                if (um[a[r]] == a[r]) cnt++;
            }
            while (l < q.l) {
                if (um[a[l]] == a[l]) cnt--;
                um[a[l]]--;
                if (um[a[l]] == a[l]) cnt++;
                l++;
            }
            while (l > q.l) {
                l--;
                if (um[a[l]] == a[l]) cnt--;
                um[a[l]]++;
                if (um[a[l]] == a[l]) cnt++;
            }
            ans[q.idx] = cnt;
        }
    }

    for (auto now : ans) cout << now << '\n';
}
