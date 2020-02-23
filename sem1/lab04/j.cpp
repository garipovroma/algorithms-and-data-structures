#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e4 + 1;

char a[N];
char b[N];
//  string a, b;
char ans[N];
int pos = 0;

int dp[N][N];
pair<int, int> p[N][N];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	scanf("%s", a);
	scanf("%s", b);
	// cin >> a >> b;
	int n = strlen(a);
	int m = strlen(b);
	//  int n = len(a);
	//  int m = len(b);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			p[i][j] = {-1, -1};
			dp[i][j] = 0;
		}
	}
	/*for (int i = 0; i < n; i++) {
		if (a[i] == b[0])
			dp[i][0] = 1;
	}
	for (int i = 0; i < m; i++) {
		if (b[i] == a[0])
			dp[0][i] = 1;
	}*/
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i - 1] == b[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
				p[i][j] = {i - 1, j - 1};
			} else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				if (dp[i][j] == dp[i - 1][j])
					p[i][j] = {i - 1, j};
				if (dp[i][j] == dp[i][j - 1])
					p[i][j] = {i, j - 1};
			}
		}
	}
	/*for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			cout << dp[i][j] << ' ';
		}
		cout << endl;
	}*/
	int i = n, j = m;
	while (dp[i][j] != 0) {
		while (j > 0 && dp[i][j] == dp[i][j - 1])
			j--;
		while (i > 0 && dp[i][j] == dp[i - 1][j])
			i--;
		ans[pos++] = a[i - 1];
		i--;
		j--;
	}
	if (pos == 0) {
		cout << endl;
	}
	for (int i = 0; i < pos; i++)
		cout << ans[pos - 1 - i];
}

