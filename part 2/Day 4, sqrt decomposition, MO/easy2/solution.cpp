#include <bits/stdc++.h>
#define int int64_t

using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int c = sqrt(n);
    vector<int> a(n, 0);
    vector<int> steps(n, 0), next(n), last(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; i++) {
        next[i] = i;
        while (next[i] < min(n, (i / c + 1) * c)) {
            steps[i]++;
            last[i] = next[i];
            next[i] += a[next[i]];
        }
    }

    while (m--) {
        int t;
        cin >> t;
        if (t == 0) {
            int idx, val;
            cin >> idx >> val;
            idx--;
            a[idx] = val;
            next[idx] = idx;
            steps[idx] = 0;
            while (next[idx] < min(n, (idx / c + 1) * c)) {
                steps[idx]++;
                last[idx] = next[idx];
                next[idx] += a[next[idx]];
            }

            for (int i = idx - 1; i >= idx / c * c; i--) {
                int to = i + a[i];
                if (to < min(n, (i / c + 1) * c)) {
                    steps[i] = steps[to] + 1;
                    next[i] = next[to];
                    last[i] = last[to];
                }
            }
        } else {
            int idx;
            cin >> idx;
            idx--;
            int cnt = 0;
            int l, ptr = idx;
            while (ptr < n) {
                cnt += steps[ptr];
                l = last[ptr];
                ptr = next[ptr];
            }
            cout << l + 1 << ' ' << cnt << '\n';
        }
    }
}
