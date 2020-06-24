#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 5e5 + 100;
const int K = 25;

int dp[N][K];
int tin[N], tout[N], timer = 1;

vector <int> g[N];

void dfs(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < K; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	}
	for (int i : g[v]) {
		if (i != p) {
			dfs(i, v);
		}
	}
	tout[v] = timer++;
}

int check_ancestor(int v, int u) {   // v - anc of u
	return (tin[v] <= tin[u] && tout[u] <= tout[v]);
}

int mega_jump(int v, int u) {
	if (check_ancestor(v, u)) {
		swap(v, u);
	}
	for (int i = K - 1; i >= 0; i--) {
		int cur = dp[v][i];
		if (!check_ancestor(cur, u)) {
			v = cur;
		}
	}
	return dp[v][0];
}

int get_lca(int v, int u) {
	if (v == u) {
		return v;
	}
	return mega_jump(v, u);
}

vector <pair<int, int>> queries;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> q;
	string s;
	int a, b;
	for (int i = 0; i < q; i++) {
		cin >> s >> a >> b;
		a--;
		b--;
		if (s == "ADD") {
			g[a].push_back(b);
			g[b].push_back(a);
		} else {
			queries.push_back({a, b});
		}
	}
	dfs(0, 0);
	for (int i = 0; i < len(queries); i++) {
		int x = queries[i].first;
		int y = queries[i].second;
		int res = get_lca(x, y) + 1;
		cout << res << "\n";
	}
	return 0;
}
