
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll NEG_INF = LLONG_MIN / 4;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.reserve(n);
    stack<int> st;
    st.push(1);
    parent[1] = -1;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            st.push(v);
        }
    }
    vector<ll> dp0(n + 1, 0);
    vector<ll> dp1(n + 1, NEG_INF);
    vector<ll> dp2(n + 1, 0);
    reverse(order.begin(), order.end());
    for (int u : order) {
        dp0[u] = a[u];
        dp2[u] = 0;
        dp1[u] = NEG_INF;
        ll bestGain = NEG_INF;
        for (int v : adj[u]) {
            if (parent[v] != u) continue;
            dp0[u] += dp2[v];
            dp2[u] += max(dp1[v], dp2[v]);
            bestGain = max(
                bestGain,
                dp0[v] - max(dp1[v], dp2[v])
            );
        }
        if (bestGain != NEG_INF) {
            dp1[u] = dp2[u] + bestGain;
        }
    }
    cout << max({dp0[1], dp1[1], dp2[1]}) << '\n';
    return 0;
}
// Time complexity: O(n)
// Space complexity: O(n)