#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const int N = 2021;
const ll M = 1e9;

ll dp[N][N];
int a[N];

void calc(int l, int r) {
	if (dp[l][r] != -1) {
		return;
	}
	if (l == r) {
		dp[l][r] = 1;
		return;
	}
	calc(l, r - 1);
	calc(l + 1, r - 1);
	calc(l + 1, r);
	if (a[l] != a[r]) {
		dp[l][r] = (dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1]);
		if (dp[l][r] >= M)
			dp[l][r] -= M;
		if (dp[l][r] >= M)
			dp[l][r] -= M;
		if (dp[l][r] >= M)
			dp[l][r] -= M;
	} else {
		dp[l][r] = dp[l + 1][r] + dp[l][r - 1] + 1;
		if (dp[l][r] >= M)
			dp[l][r] -= M;
		if (dp[l][r] >= M)
			dp[l][r] -= M;
		if (dp[l][r] >= M)
			dp[l][r] -= M;
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (j >= i)
				dp[i][j] = 1;
		}
	}
	for (int len = 2; len <= n; len++) {
		for (int l = 1; l + len - 1 <= n; l++) {
			int r = (l + len - 1);
			//   cout << len << ' ' << l << ' ' << r << endl;
			if (a[l] != a[r]) {
				dp[l][r] = (dp[min(n, l + 1)][r]
					+ dp[l][max(1, r - 1)] - dp[min(n, l + 1)][max(1, r - 1)] + M);
			} else {
				dp[l][r] = dp[min(n, l + 1)][r] + dp[l][max(1, r - 1)] + 1;
			}
			dp[l][r] %= M;
		}
	}
	cout << dp[1][n] % M;
	return 0;
}

