#include <bits/stdc++.h>
#define int int64_t
#define bint __int128_t

using namespace std;

int n;
vector<vector<vector<int>>> tree;

bint sum(int x, int y, int z) {
    bint res = 0;
    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j)
            for (int g = z; g > 0; g -= g & -g) res += tree[i][j][g];
    return res;
}

void update(int k, int x, int y, int z) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= n; j += j & -j)
            for (int g = z; g <= n; g += g & -g) {
                tree[i][j][g] += k;
            }
}

bint getSum(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) - sum(x2, y2, z1 - 1) + sum(x1 - 1, y1 - 1, z2) + sum(x1 - 1, y2, z1 - 1) + sum(x2, y1 - 1, z1 - 1) - sum(x1 - 1, y1 - 1, z1 - 1);
}

void print(bint x) {
    if (x == 0) {
        cout << 0 << '\n';
        return;
    }
    if (x < 0) {
        cout << '-';
        x = -x;
    }
    vector<char> ans;
    while (x > 0) {
        ans.emplace_back((x % 10) + '0');
        x /= 10;
    }
    reverse(ans.begin(), ans.end());
    for (auto c : ans) cout << c;
    cout << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int q;
    cin >> n >> q;
    tree.resize(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, 0)));

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y, z, k;
            cin >> x >> y >> z >> k;
            update(k, x + 1, y + 1, z + 1);
        } else {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            print(getSum(x1 + 1, y1 + 1, z1 + 1, x2 + 1, y2 + 1, z2 + 1));
        }
    }
}
