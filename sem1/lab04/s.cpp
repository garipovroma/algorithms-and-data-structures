#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const ll M = 999999937;

vector <vector<ll>> begMatrix;

vector <vector<ll>> prod(vector <vector<ll>> &a, vector<vector<ll>> &b) {
    int n = len(a);
    int m = len(b[0]);
    vector <vector<ll>> res(len(a), vector<ll>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int x = 0; x < len(a[i]); x++) {
                res[i][j] += (a[i][x] * b[x][j]) % M;
            }
            res[i][j] %= M;
        }
    }
    return res;
}

vector <vector<ll>> bin_pow(vector <vector<ll>> cur, ll n) {
	if (n == 0) {
		cur[0] = {1, 0, 0, 0, 0};
		cur[1] = {0, 1, 0, 0, 0};
		cur[2] = {0, 0, 1, 0, 0};
		cur[3] = {0, 0, 0, 1, 0};
		cur[4] = {0, 0, 0, 0, 1};
		return cur;
	}
    if (n == 1)
        return cur;
    if (n % 2 == 0) {
        vector <vector<ll>> curr = bin_pow(cur, n / 2);
        return prod(curr, curr);
    } else {
        vector <vector<ll>> curr = bin_pow(cur, n - 1);
        return prod(curr, cur);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  //   HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n;
    begMatrix.resize(5, vector<ll>(1, 1));
    vector <vector<ll>> kek;
    kek.resize(5);
    kek[0] = {1, 1, 1, 1, 1};
    kek[1] = {1, 1, 1, 1, 1};
    kek[2] = {1, 1, 1, 0, 0};
    kek[3] = {1, 1, 1, 1, 1};
    kek[4] = {1, 1, 1, 0, 0};
    while (cin >> n) {
        if (n == 0) {
            return 0;
        }
        vector <vector<ll>> curMatrix = bin_pow(kek, n - 1);
        vector <vector<ll>> ans = prod(curMatrix, begMatrix);
        ll sum = 0;
        for (int i = 0; i < 5; i++)
            sum += ans[i][0];
        sum %= M;
        cout << sum << "\n";
    }
    return 0;
}

