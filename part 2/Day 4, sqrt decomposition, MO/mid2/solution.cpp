#include <bits/stdc++.h>
#define int int32_t

using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, t;
    cin >> n >> t;
    const int c = sqrt(n);
    vector<int> ans(t, 0);
    vector<vector<int>> arr(t, vector<int>(c, 0));

    for (int i = 0; i < n; i++) {
        int from, d;
        cin >> from >> d;
        if (from > t) continue;
        from--;
        if (d >= c)
            for (int j = from; j < t; j += d) ans[j]++;
        else
            arr[from][d]++;
    }
    for (int i = 0; i < t; i++) {
        for (int j = 1; j < c; j++) {
            int cnt = arr[i][j];
            ans[i] += cnt;
            if (i + j < t) arr[i + j][j] += cnt;
        }
    }
    for (auto now : ans) cout << now << ' ';
}