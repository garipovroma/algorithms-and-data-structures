#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const int N1 = 10001;
const int N2 = 1001;

int dp[N1][N2];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("knapsack.in", "rt", stdin);
	freopen("knapsack.out", "wt", stdout);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector <int> c(n), w(n);
	for (int i = 0; i < n; i++) {
		cin >> w[i];
	}
	bool kek = true;
	for (int i = 0; i < n; i++) {
		if (w[i] <= m) kek = false;
	}
	if (kek) {
		cout << "0";
		return 0;
	}
	for (int i = 0; i < n; i++) {
		cin >> c[i];
	}
	vector <vector <int>> dp(n, vector<int>(m + 1, 0));
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		dp[i][w[i]] = c[i];
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			dp[i][j] = dp[i - 1][j];
			int x = j - w[i];
			if (x >= 0 && dp[i - 1][x] + c[i] > dp[i][j]) {
				dp[i][j] = dp[i - 1][x] + c[i];
			}
		}
	}
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << dp[i][j] << ' ';
		cout << endl;
	}*/
	int mx = 0;
	for (int i = 0; i <= m; i++) {
		if (dp[n - 1][i] > dp[n - 1][mx]) {
			mx = i;
		}
	}
	vector <int> ans;
	int x = n - 1;
	int y = mx;
	while (x > 0) {
		if (dp[x - 1][y] != dp[x][y]) {
			ans.push_back(x);
			y -= w[x];
		}
		x--;
	}
	if (y != 0)
		ans.push_back(x);
	reverse(all(ans));
	cout << len(ans) << "\n";
	for (int i : ans)
		cout << i + 1 << ' ';
	return 0;
}
