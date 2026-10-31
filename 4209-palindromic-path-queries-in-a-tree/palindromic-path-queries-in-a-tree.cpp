
class Solution {
    static const int LOG = 16;

    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth, tin, tout, prefix;
    vector<int> bit;

    struct Fenwick {
        int n;
        vector<int> tree;

        Fenwick(int n) {
            this->n = n;
            tree.assign(n + 2, 0);
        }

        void add(int i, int val) {
            for (i++; i <= n + 1; i += i & -i) {
                tree[i] ^= val;
            }
        }

        void rangeXor(int l, int r, int val) {
            add(l, val);
            add(r + 1, val);
        }

        int query(int i) {
            int ans = 0;

            for (i++; i > 0; i -= i & -i) {
                ans ^= tree[i];
            }

            return ans;
        }
    };

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];

        for (int k = 0; k < LOG; k++) {
            if (diff & (1 << k)) {
                u = up[k][u];
            }
        }

        if (u == v) return u;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        bit.resize(n);

        for (int i = 0; i < n; i++) {
            bit[i] = 1 << (s[i] - 'a');
        }

        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        prefix.assign(n, 0);

        up.assign(LOG, vector<int>(n, 0));

        // Iterative DFS
        vector<int> parent(n, -1);
        vector<int> order;
        vector<int> st;

        st.push_back(0);
        parent[0] = 0;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            tin[u] = order.size();
            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                prefix[v] = prefix[u] ^ bit[v];

                st.push_back(v);
            }
        }

        // Build binary lifting table
        for (int i = 0; i < n; i++) {
            up[0][i] = parent[i];
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        // Calculate subtree sizes
        vector<int> sz(n, 1);

        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            sz[parent[u]] += sz[u];
        }

        for (int u = 0; u < n; u++) {
            tout[u] = tin[u] + sz[u] - 1;
        }

        Fenwick fw(n);

        vector<bool> ans;

        for (string& q : queries) {
            string type;
            int u;

            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int newBit = 1 << (c - 'a');
                int delta = bit[u] ^ newBit;

                fw.rangeXor(tin[u], tout[u], delta);

                bit[u] = newBit;
            }
            else {
                int v;
                ss >> v;

                int w = lca(u, v);

                int pu = prefix[u] ^ fw.query(tin[u]);
                int pv = prefix[v] ^ fw.query(tin[v]);

                int pathMask = pu ^ pv ^ bit[w];

                ans.push_back(
                    __builtin_popcount((unsigned int)pathMask) <= 1
                );
            }
        }

        return ans;
    }
};
