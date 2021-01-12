#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5 + 100;

vector <int> g[N];
vector <int> dp;

void dfs(int v) {
	for (int i : g[v]) {
		if (dp[i] == -1) {
			dfs(i);
		}
	}
	if (len(g[v]) == 0) {
		dp[v] = 0;
	} else {
		bool was = false;
		for (int i : g[v]) {
			if (dp[i] == 0) {
				was = true;
			}
		}
		if (was) {
			dp[v] = 1;
		} else {
			dp[v] = 0;
		}
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, s;
	cin >> n >> m >> s;
	s--;
	dp.resize(n, -1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
	}
	dfs(s);
	if (dp[s] == 0) {
		cout << "Second player wins";
	} else {
		cout << "First player wins";
	}
	return 0;
}
