#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 210;

vector <int> g[N];
vector <int> edge;
vector <bool> used;

bool dfs(int v) {
	if (used[v]) {
		return false;
	}
	used[v] = true;
	for (int i : g[v]) {
		if (edge[i] == -1 || dfs(edge[i])) {
			edge[i] = v;
			return true;
		}
	}
	return false;
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		g[x].push_back(y);
	}
	edge.assign(m, -1);
	for (int i = 0; i < n; i++) {
		used.assign(n, false);
		dfs(i);
	}
	int ans = 0;
	for (int i = 0; i < m; i++) {
		if (edge[i] != -1) {
			ans++;
		}
	}
	cout << ans;
	return 0;
}
