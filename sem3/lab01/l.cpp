#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 2e4 + 100;

vector <int> tin;
vector <pair<int, int>> g[N];
vector <int> fup;
vector <int> colors, used;
vector <int> cutpoint;

int timer = 0;
int max_color = 0;

void dfs(int v, int p = -1) {
	fup[v] = tin[v] = ++timer;
	int count = 0;
	for (auto x : g[v]) {
		int i = x.first;
		if (tin[i] != -1 && i != p) {
			fup[v] = min(fup[v], tin[i]);
		} else if (tin[i] == -1) {
			dfs(i, v);
			fup[v] = min(fup[v], fup[i]);
			count++;
		}
	}
}

void colorize(int v, int color, int p) {
	used[v] = 1;
	for (auto x : g[v]) {
		int i = x.first;
		int id = x.second;
		if (used[i] == 0 && i != p) {
			if (fup[i] >= tin[v]) {
				colors[id] = ++max_color;
				colorize(i, max_color, v);
			} else {
				colors[id] = color;
				colorize(i, color, v);
			}
		} else if (tin[i] < tin[v]) {
			colors[id] = color;
		}
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back({b, i});
		g[b].push_back({a, i});
	}
	fup.resize(n, 1e9);
	tin.resize(n, -1);
	dfs(0);
	used.resize(n, 0);
	colors.resize(m, 0);
	colorize(0, 0, -1);
	cout << max_color << "\n";
	for (int i = 0; i < m; i++) {
		cout << colors[i] << ' ';
	}
	return 0;
}
