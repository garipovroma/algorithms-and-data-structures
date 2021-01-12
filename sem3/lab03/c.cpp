#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 4000;

vector<vector <int>> g, g_r, g_l;
vector <int> r_mt, l_mt;
vector <bool> used_l, used_r;

void dfs(int v, vector <bool> &used, vector<vector<int>> &gg, bool left) {
	used[v] = true;
	for (int i : gg[v]) {
		bool was = (left ? used_r[i] : used_l[i]);
		if (was) {
			continue;
		}
		if (left) {
			dfs(i, used_r, g_r, false);
		} else {
			dfs(i, used_l, g_l, true);
		}
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> m >> n;
	g.resize(m);
	for (int i = 0; i < m; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int x;
			cin >> x;
			x--;
			g[i].push_back(x);
		}
	}
	r_mt.resize(n, -1);
	l_mt.resize(m);
	for (int i = 0; i < m; i++) {
		cin >> l_mt[i];
		l_mt[i]--;
		if (l_mt[i] != -1) {
			r_mt[l_mt[i]] = i;
		}
	}
	g_l.resize(m);
	g_r.resize(n);
	for (int i = 0; i < m; i++) {
		if (l_mt[i] == -1) {
			for (auto j : g[i]) {
				g_l[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (r_mt[i] != -1) {
			g_r[i].push_back(r_mt[i]);
		}
	}
	used_l.resize(m, false);
	used_r.resize(n, false);
	for (int i = 0; i < m; i++) {
		if (l_mt[i] == -1 && !used_l[i]) {
			dfs(i, used_l, g_l, true);
		}
	}
	vector<int> v_l, v_r;
	for (int i = 0; i < m; i++) {
		if (!used_l[i]) {
			v_l.push_back(i);
		}
	}
	for (int i = 0; i < n; i++) {
		if (used_r[i]) {
			v_r.push_back(i);
		}
	}
	cout << len(v_l) + len(v_r) << "\n" << len(v_l) << " ";
	for (int i : v_l) {
		cout << i + 1 << ' ';
	}
	cout << "\n" << len(v_r) << " ";
	for (int i : v_r) {
		cout << i + 1 << ' ';
	}
	return 0;
}
