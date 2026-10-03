#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> U(n), Vv(n);
    vector<ll> single(n), multi(n);
    for (int eid = 1; eid <= n - 1; eid++) {
        int u, v;
        ll s, m;
        cin >> u >> v >> s >> m;
        U[eid] = u;
        Vv[eid] = v;
        single[eid] = s;
        multi[eid] = m;
        adj[u].push_back({v, eid});
        adj[v].push_back({u, eid});
    }
    vector<int> seq(n);
    iota(seq.begin(), seq.end(), 1);
    int LOG = 1;
    while ((1 << LOG) <= n) LOG++;
    vector<int> depth(n + 1, 0), parent(n + 1, 0);
    vector<vector<int>> up(LOG, vector<int>(n + 1, 0));
    function<void(int, int)> dfs0 = [&](int u, int p){
        parent[u] = p;
        up[0][u] = p;
        for (auto [v, eid] : adj[u]) {
            if (v==p) continue;
            depth[v] = depth[u] + 1;
            dfs0(v, u);
        }
    };
    dfs0(1, 0);
    for (int k = 1; k < LOG; k++) {
        for (int v = 1; v <= n; v++) up[k][v] = up[k - 1][up[k - 1][v]];
    }
    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int k = 0; k < LOG; k++) if (diff & (1 << k)) a = up[k][a];
        if (a == b) return a;
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][a] != up[k][b]) {
                a = up[k][a];
                b = up[k][b];
            }
        }
        return up[0][a];
    };
    vector<ll> diffnode(n + 1, 0);
    for (int i = 0; i + 1 < (int)seq.size(); i++) {
        int a = seq[i], b = seq[i + 1];
        int w = lca(a, b);
        diffnode[a] += 1;
        diffnode[b] += 1;
        diffnode[w] -= 2;
    }
    vector<ll> cnt(n, 0);
    ll total = 0;
    function<ll(int, int)> dfs1 = [&](int u, int p)->ll {
        ll subtotal = diffnode[u];
        for (auto [v, eid] : adj[u]) {
            if (v == p) continue;
            ll s = dfs1(v, u);
            cnt[eid] = s;
            total += min(s * single[eid], multi[eid]);
            subtotal += s;
        }
        return subtotal;
    };
    dfs1(1, 0);
    cout << total << endl;
    return 0;
}
//Time complexity: O(n * logn)
//Space complexity: O(n * logn)