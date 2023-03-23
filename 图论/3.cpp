#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
using pii = pair<int, int>;

const int N = 30;
int n, m, A[N][N];
vector<pii> e;

int judge(int k) { 
// 使用前 k 个不等式能够确定所有的关系返回 1
// 使用前 k 个不等式出现矛盾返回 2
// 使用前 k 个不等式既不能确定所有关系也没有出现矛盾则返回 3
    memset(A, 0, sizeof A);
    for (int i = 0; i < k; i++) {
        A[e[i].first][e[i].second] = 1;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                A[i][j] |= A[i][k] & A[k][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        if (A[i][i]) return 2;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++)
            if (!A[i][j] && !A[j][i])
                return 3; 
    }
    return 1;
}

int main() {
    freopen("1.in", "r", stdin);
    while (cin >> n >> m && n && m) {
        while (e.size()) e.pop_back();

        for (int i = 1; i <= m; i++) {
            string str;
            cin >> str;
            e.push_back( {str[0] - 'A' + 1, str[2] - 'A' + 1} );
        }

        int num1 = 0, num2 = 0;
        for (int i = 1; i <= m; i++) {
            int t = judge(i);
            if (t == 1) { num1 = i; break; }
            else if (t == 2) { num2 = i; break; }
        }

        if (num2) printf("Inconsistency found after %d relations.\n", num2);
        else if (num1) {
            printf("Sorted sequence determined after %d relations: ", num1);
            vector<int> cnt(n + 1);
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++)
                    if (A[i][j]) cnt[i]++;
            }
            for (int i = n - 1; i >= 0; i--) {
                for (int j = 1; j <= n; j++)
                    if (cnt[j] == i) {
                        cout << char('A' + j - 1);
                        break;
                    }
            }
            cout << ".\n";
        } else printf("Sorted sequence cannot be determined.\n");
    }
}