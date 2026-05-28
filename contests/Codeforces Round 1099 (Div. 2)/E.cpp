#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, d;
    cin >> n >> d;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--;
      v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    vector<int> order, par(n, -1), sz(n, 1);
    vector<bool> vis(n, false);
    order.push_back(0);
    vis[0] = true;
    for (int i = 0; i < (int)order.size(); i++) {
      for (int u : adj[order[i]]) {
        if (!vis[u]) {
          vis[u] = true;
          par[u] = order[i];
          order.push_back(u);
        }
      }
    }
    for (int i = n - 1; i >= 0; i--) {
      int v = order[i];
      if (par[v] >= 0)
        sz[par[v]] += sz[v];
    }
    vector<vector<array<long long, 4>>> dp(n);

    for (int i = n - 1; i >= 0; i--) {
      int v = order[i];
      vector<int> ch;
      for (int u : adj[v])
        if (par[u] == v)
          ch.push_back(u);
      int cur = 0;
      vector<array<long long, 4>> mg(1, {1, 0, 0, 0});

      for (int c : ch) {
        int csz = sz[c];
        int nsz = cur + csz;
        vector<array<long long, 4>> nmg(min(nsz, d) + 1, {0, 0, 0, 0});

        for (int j = 0; j <= min(cur, d); j++) {
          for (int m = 0; m <= 3; m++) {
            if (!mg[j][m])
              continue;
            for (int j2 = 0; j2 < (int)dp[c].size(); j2++) {
              for (int m2 = 0; m2 <= 3 - m; m2++) {
                if (!dp[c][j2][m2])
                  continue;
                int ec = (m2 >= 1 && m2 <= 2) ? 1 : 0;
                int nj = j + j2 + ec;
                if (nj >= (int)nmg.size())
                  continue;
                nmg[nj][m + m2] += mg[j][m] * dp[c][j2][m2];
              }
            }
          }
        }
        mg = move(nmg);
        cur = nsz;
      }

      int lim = min(cur, d - 1);
      dp[v].resize(lim + 1, {0, 0, 0, 0});
      for (int j = 0; j <= lim; j++) {
        if (j >= (int)mg.size())
          break;
        for (int m = 0; m <= 3; m++) {
          dp[v][j][m] += mg[j][m];
          if (m >= 1)
            dp[v][j][m] += mg[j][m - 1];
        }
      }
    }

    long long ans = 0;
    if (d - 1 < (int)dp[0].size())
      ans = dp[0][d - 1][3];
    cout << ans << "\n";
  }
  return 0;
}
