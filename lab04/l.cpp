#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const int N = 1e5 + 10;

vector <int> g[N];
vector <ll> cost[N];

vector <vector<ll>> dp;

void dfs(int v, int p) {
	// cout << v << ' ' << p << endl;
	for (int i : g[v]) {
		if (i != p) {
			dfs(i, v);
		}
	}
	for (int i : g[v]) {
		if (i != p)
			dp[v][0] += dp[i][2];
	}
	ll sum = 0;
	for (int i : g[v])
		if (i != p)
			sum += dp[i][2];
	for (int j = 0; j < len(g[v]); j++) {
		int i = g[v][j];
		if (i == p) continue;
		dp[v][1] = max(dp[v][1], sum - dp[i][2] + cost[v][j] + dp[i][0]);
	}
	dp[v][2] = max(dp[v][1], dp[v][0]);
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("matching.in", "rt", stdin);
	freopen("matching.out", "wt", stdout);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	dp.resize(n, vector<ll>(3, 0));
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
		cost[a].push_back(c);
		cost[b].push_back(c);
	}
	dfs(0, -1);
	cout << dp[0][2];
	return 0;
}
