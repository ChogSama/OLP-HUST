#include <bits/stdc++.h>
using namespace std;
vector<int> z_algorithm(const string &s) {
    int n = s.size();
    vector<int> Z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            Z[i] = min(r - i + 1, Z[i - l]);
        }
        while (i + Z[i] < n and s[Z[i]] == s[i + Z[i]]) {
            Z[i]++;
        }
        if (i + Z[i] - 1 > r) {
            l = i, r = i + Z[i] - 1;
        }
    }
    return Z;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    int T1 = T;
    vector<long long> res;
    while (T--) {
        string s;
        cin >> s;
        vector<int> Z = z_algorithm(s);
        long long total = s.size();
        for (int z : Z) total += z;
        res.push_back(total);
    }
    for (long long x : res) cout << x << endl;
    return 0;
}
//Time complexity: O(n)
//Space complexity: O(n)