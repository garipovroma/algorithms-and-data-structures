#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 5e5 + 100;
const int K = 25;

int dp[N][K];
int tin[N], tout[N], timer = 1;
int hh[N];

vector <int> g[N];

void dfs(int v, int p, int h) {
	tin[v] = timer++;
	dp[v][0] = p;
	hh[v] = h;
	for (int i = 1; i < K; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	}
	for (int i : g[v]) {
		if (i != p) {
			dfs(i, v, h + 1);
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
	int n;
	while (cin >> n) {
		if (n == 0) {
			return 0;
		}
		for (int i = 0; i < n - 1; i++) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		int m;
		cin >> m;
		int current_root = -1;
		dfs(0, 0, 0);
		for (int i = 0; i < m; i++) {
			char c;
			cin >> c;
			if (c == '!') {
				int x;
				cin >> x;
				x--;
				current_root = x;
			} else {
				int a, b;
				cin >> a >> b;
				a--;
				b--;
				int cur = get_lca(a, b);
				int cur2 = get_lca(current_root, a);
				int cur3 = get_lca(current_root, b);
				int ans = -1, d = -1;
				if (hh[cur] > d) {
					ans = cur;
					d = hh[cur];
				}
				if (hh[cur2] > d) {
					ans = cur2;
					d = hh[cur2];
				}
				if (hh[cur3] > d) {
					ans = cur3;
					d = hh[cur3];
				}
				cout << ans + 1 << "\n";
			}
		}
		for (int i = 0; i < n; i++) {
			g[i].clear();
			hh[i] = 0;
			tin[i] = tout[i] = 0;
			timer = 0;
			for (int j = 0; j < K; j++)
				dp[i][j] = 0;
		}
	}
	return 0;
}
