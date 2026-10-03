#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    int maxVal = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            maxVal = max(maxVal, a[i][j]);
        }
    }
    vector<bool> isPrime(maxVal + 1, true);
    if (maxVal >= 0) isPrime[0] = false;
    if (maxVal >= 1) isPrime[1] = false;
    for (int i = 2; 1LL * i * i <= maxVal; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= maxVal; j += i) {
                isPrime[j] = false;
            }
        }
    }
    int ans = 0;
    for (int p = 2; p <= maxVal; p++) {
        if (!isPrime[p]) continue;
        vector<int> heights(m, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] % p == 0)
                    heights[j]++;
                else
                    heights[j] = 0;
            }
            stack<int> st;
            for (int j = 0; j <= m; j++) {
                int h = (j == m ? 0 : heights[j]);
                while (!st.empty() && heights[st.top()] > h) {
                    int height = heights[st.top()];
                    st.pop();
                    int width = st.empty() ? j : j - st.top() - 1;
                    ans = max(ans, height * width);
                }
                st.push(j);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
// Time complexity: O(n * m * log(maxVal))
// Space complexity: O(maxVal + m)