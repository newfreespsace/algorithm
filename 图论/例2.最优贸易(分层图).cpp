#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int n, m, A[N];
vector<int> e[N];
int d[3][N];
bool inq[3][N];

void spfa() {
  memset(d, 0xaf, sizeof d);
  d[0][1] = 0;
  queue<pair<int, int>> q;
  q.push({0, 1});
  inq[0][1] = true;

  while (q.size()) {
    auto t = q.front();
    q.pop();
    int f = t.first, s = t.second;
    inq[f][s] = false;
    if (f == 0 && d[f + 1][s] < d[f][s] - A[s]) {
      d[f + 1][s] = d[f][s] - A[s];
      if (!inq[f + 1][s])
        q.push({f + 1, s}), inq[f + 1][s] = true;
    }

    if (f == 1 && d[f + 1][s] < d[f][s] + A[s]) {
      d[f + 1][s] = d[f][s] + A[s];
      if (!inq[f + 1][s])
        q.push({f + 1, s}), inq[f + 1][s] = true;
    }

    for (auto y : e[s]) {
      if (d[f][y] < d[f][s]) {
        d[f][y] = d[f][s];
        if (!inq[f][y])
          q.push({f, y}), inq[f][y] = true;
      }
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> A[i];
  for (int i = 1; i <= m; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    e[x].push_back(y);
    if (z == 2) e[y].push_back(x);
  }

  spfa();
  cout << d[2][n] << endl;
}