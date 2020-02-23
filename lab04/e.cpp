#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const int N = 5001;

int dp[N][N];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("levenshtein.in", "rt", stdin);
	freopen("levenshtein.out", "wt", stdout);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string a, b;
	cin >> a >> b;
	int n = len(a), m = len(b);
	a = "#" + a;
	b = "#" + b;
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = i;
	}
	for (int i = 1; i <= m; i++) {
		dp[0][i] = i;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i] == b[j]) {
				dp[i][j] = dp[i - 1][j - 1];
			} else {
				int a = dp[i - 1][j] + 1;
				int b = dp[i][j - 1] + 1;
				int c = dp[i - 1][j - 1] + 1;
				dp[i][j] = min(min(a, b), c);
			}
		}
	}
	cout << dp[n][m];
	return 0;
}

