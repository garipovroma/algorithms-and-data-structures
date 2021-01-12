#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

struct kuhn {
	int n, m, k;
	vector <vector<int>> g;
	vector <int> edge;
	vector <bool> used;

	void read_bigraph() {
		g.resize(n);
		cin >> n >> m >> k;
		for (int i = 0; i < k; i++) {
			int x, y;
			cin >> x >> y;
			x--;
			y--;
			g[x].push_back(y);
		}
	}

	void build_graph_for_path_minimisation(vector<vector<int>> &gg) {
		n = len(gg);
		m = len(gg);
		g.resize(n);
		map<pair<int, int>, bool> was;
		for (int i = 0; i < len(gg); i++) {
			for (int j : gg[i]) {
				g[i].push_back(j);
				k++;
			}
		}
	}

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

	int get_matching() {
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
		return ans;
	}
};

kuhn s;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		g[x].push_back(y);
	}
	s.build_graph_for_path_minimisation(g);
	cout << n - s.get_matching();
	return 0;
}
