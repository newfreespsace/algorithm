#include <bits/stdc++.h>

using namespace std;
const int N = 1000 + 5, M = 2e4 + 10;
int n, p, k, d[N];
int ne[M], ver[M], edge[M], head[N], tot;
void add(int u, int v, int w) {
  edge[++tot] = w;
  ver[tot] = v;
  ne[tot] = head[u];
  head[u] = tot;
}

bool check(int cost) {// 花费不超过 x 是否可行，计算 1 到 n 的最短路，若花费大于 x，则边长记为 1，否则记为 0
  deque<int> q;
  memset(d, 0x3f, sizeof d);
  q.push_front(1);
  d[1] = 0;
  while (q.size()) {
    int x = q.front(); q.pop_front();
    for (int i = head[x]; i; i = ne[i]) {
      int y = ver[i], z = edge[i] > cost ? 1 : 0;
      if (d[y] > d[x] + z) {
        d[y] = d[x] + z;
        if (z == 0) q.push_front(y);
        else q.push_back(y); 
      }
    }
  }
  
  return d[n] <= k;
}

int main() {
  cin >> n >> p >> k;
  for (int i = 1; i <= p; i++) {
    int a, b, l;
    cin >> a >> b >> l;
    add(a, b, l);
    add(b, a, l);
  }  
  int l = 0, r = int(1e9);
  while (l < r) {
    int mid = l + r >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }
  cout << (r == int(1e9) ? -1 : l) << endl;
}