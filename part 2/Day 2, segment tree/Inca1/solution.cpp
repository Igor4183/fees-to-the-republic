#include <bits/stdc++.h>
#define int int64_t

using namespace std;

void erase_sub(set<pair<int, int>>& s, int l, int r, int& ans) {
    auto it = s.lower_bound(make_pair(l, 0LL));
    while (it != s.end() and it->second <= r) {
        int tl = it->second, tr = it->first;
        ans += max(0LL, min(tr, r) - max(tl, l) + 1);

        s.erase(it);
        if (tl < l) s.insert({l - 1, tl});
        if (r < tr) s.insert({tr, r + 1});
        it = s.lower_bound(make_pair(l, 0LL));
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, ans;
    cin >> n >> m;
    ans = n;
    set<pair<int, int>> s; // {r,l}

    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        erase_sub(s, l, r, ans);
        if (k == 1) {
            ans -= r - l + 1;
            s.insert({r, l});
        }
        // for (auto now : s) cout << "{" << now.second << ", " << now.first << "} ";
        cout << ans << '\n';
    }
}
