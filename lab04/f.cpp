#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const int N = 10002;

bool dp[N][N];
bool f[N][N];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string a, b;
	cin >> a >> b;
	int n = len(a);
	int m = len(b);
	a = "##" + a;
	b = "##" + b;
	dp[0][0] = true;
	for (int i = 1; i <= m + 1; i++) {
		for (int j = 1; j <= n + 1; j++) {
			if (a[j] == '?') {
				dp[i][j] = dp[i - 1][j - 1];
			} else if (a[j] == '*') {
				dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
			} else {
				bool cur = (a[j] == b[i]);
				dp[i][j] = dp[i - 1][j - 1] && cur;
			}
		}
	}
	/*
	for (int i = 1; i <= m + 1; i++) {
		for (int j = 1; j <= n + 1; j++) {
			cout << dp[i][j] << ' ';
		}
		cout << endl;
	} */
	if (dp[m + 1][n + 1])
		cout << "YES";
	else
		cout << "NO";
	return 0;
}

