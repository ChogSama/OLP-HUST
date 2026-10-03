#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int m, n;
    cin >> m >> n;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> valid;
    for (int mask = 0; mask < (1 << n); mask++) {
        if ((mask & (mask << 1)) == 0){
            valid.push_back(mask);
        }
    }
    vector<vector<int>> dp(m, vector<int>(1 << n, INT_MIN));
    for (int mask : valid) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) sum += a[0][j];
        }
        dp[0][mask] = sum;
    }
    for (int i = 1; i < m; i++) {
        for (int mask : valid) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) sum += a[i][j];
            }
            for (int pmask : valid) {
                if ((mask & pmask) == 0) {
                    dp[i][mask] = max(dp[i][mask], dp[i - 1][pmask] + sum);
                }
            }
        }
    }
    int ans = INT_MIN;
    for (int mask : valid) ans = max(ans, dp[m - 1][mask]);
    cout << ans << endl;
    return 0;
}
//Time complexity: O(m * (2^n)^2)
//Space complexity: O(m * 2^n)