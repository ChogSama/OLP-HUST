
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int solve(int n, int m, const string& s, const string& t) {
    if (m > n || s[0] != t[0]) {
        return -1;
    }
    vector<int> prev(n, INF), cur(n, INF);
    prev[0] = 0;
    for (int j = 1; j < m; ++j) {
        fill(cur.begin(), cur.end(), INF);
        int prefixMin = INF;
        for (int i = 0; i < n; ++i) {
            if (i >= 2) {
                prefixMin = min(prefixMin, prev[i - 2]);
            }
            if (s[i] != t[j]) {
                continue;
            }
            if (i >= 1) {
                cur[i] = min(cur[i], prev[i - 1]);
            }
            if (prefixMin != INF) {
                cur[i] = min(cur[i], prefixMin + 1);
            }
        }
        swap(prev, cur);
    }
    int ans = INF;
    for (int i = 0; i < n; ++i) {
        if (prev[i] == INF) {
            continue;
        }
        int cost = prev[i] + (i < n - 1 ? 1 : 0);
        ans = min(ans, cost);
    }

    return ans == INF ? -1 : ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        int n, m;
        string s, t;
        cin >> n >> m;
        cin >> s >> t;
        cout << solve(n, m, s, t) << '\n';
    }
    return 0;
}
// Time complexity: O(n * m)
// Space complexity: O(n)