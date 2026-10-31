class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        const int MAXX = 1024;

        vector<vector<bool>> dp(n, vector<bool>(MAXX, false));

        for (int i = 0; i < m; i++) {
            vector<vector<bool>> curr(n, vector<bool>(MAXX, false));

            for (int j = 0; j < n; j++) {
                int val = grid[i][j];

                if (i == 0 && j == 0) {
                    curr[j][val] = true;
                    continue;
                }

                for (int x = 0; x < MAXX; x++) {
                    int prev = x ^ val;

                    bool fromTop = (i > 0 && dp[j][prev]);
                    bool fromLeft = (j > 0 && curr[j - 1][prev]);

                    if (fromTop || fromLeft) {
                        curr[j][x] = true;
                    }
                }
            }

            dp = curr;
        }

        for (int x = 0; x < MAXX; x++) {
            if (dp[n - 1][x]) {
                return x;
            }
        }

        return 0;
    }
};