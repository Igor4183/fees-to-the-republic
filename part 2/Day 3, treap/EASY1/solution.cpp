#include <bits/stdc++.h>
#define int int64_t

using namespace std;

priority_queue<int, vector<int>, less<int>> l;
priority_queue<int, vector<int>, greater<int>> r;

void bal() {
    while (r.size() > l.size() + 1) {
        l.push(r.top());
        r.pop();
    }
    while (r.size() < l.size()) {
        r.push(l.top());
        l.pop();
    }
    while (!l.empty() and l.top() > r.top()) {
        r.push(l.top());
        l.pop();
        l.push(r.top());
        r.pop();
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;

    // l.push(1);
    // l.push(2);
    // r.push(1);
    // r.push(2);
    // cout << l.top() << ' ' << r.top();
    // return 0;

    while (cin >> str) {
        if (str != "#") {
            r.push(stoi(str));
            bal();
        } else {
            cout << r.top() << '\n';
            r.pop();
            bal();
        }
    }
}
