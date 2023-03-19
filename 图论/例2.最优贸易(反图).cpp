#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;
int head[N], tot;
int ver[M], edge[M], nxt[M];

void add(int u, int v, int w) {
  ver[++tot] = v;
  edge[tot] = w;
  nxt[tot] = head[u];
  head[u] = tot;
}

bool vis[N];
int n, m, A[N];
int pre[N], f[N], d[N];
queue<int> q;
void spfa(int *d, int st, int z) {
  d[st] = A[st];
  q.push(st);
  vis[st] = 1;
  while (q.size()) {
    int x = q.front(); q.pop();
    vis[x] = 0;
    for (int i = head[x]; i; i = nxt[i]) {
      int y = ver[i], w = edge[i];
      if (w == 2 || w == z) {
        int val = z == 1 ? min(d[x], A[y]) : max(d[x], A[y]);
        if (z == 1 && d[y] > val || z == -1 && d[y] < val) {
          d[y] = val;
          if (!vis[y]) {
            q.push(y);
            vis[y] = 1;
          }
        }
      }
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> A[i];
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    add(x, y, z);
    add(y, x, z == 1 ? -1 : z);
  }
  memset(d, 0x3f, sizeof d);
  spfa(d, 1, 1);
  spfa(f, n, -1);

  int ans = 0;
  for (int i = 1; i <= n; i++) ans = max(ans, f[i] - d[i]);

  cout << ans << endl;
}