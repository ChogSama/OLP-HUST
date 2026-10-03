#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) cin >> arr[i];
    vector<vector<long long>> dp(N, vector<long long>(K + 1, 0));
    for (int i = 0; i < N; i++) dp[i][1] = 1;
    for (int k = 2; k <= K; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] > arr[i]) {
                    dp[i][k] += dp[j][k - 1];
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < N; i++) ans += dp[i][K];
    cout << ans << endl;
    return 0;
}
//Time complexity: O(N^2 * K)
//Space complexity: O(N * K)