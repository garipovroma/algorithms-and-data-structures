#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 2e4 + 100;

vector <int> g[N];
vector <int> fup, tin, color;
int timer = 1;
stack <int> s;
int cur_color = 1;

void dfs(int v, int p = -1) {
	s.push(v);
	fup[v] = tin[v] = timer++;
	for (int i : g[v]) {
		if (tin[i] != -1 && p != i) {
			fup[v] = min(fup[v], tin[i]);
		} else if (tin[i] == -1) {
			dfs(i, v);
			fup[v] = min(fup[v], fup[i]);
			if (fup[i] > tin[v]) {
				while (!s.empty()) {
					int x = s.top();
					color[x] = cur_color;
					s.pop();
					if (x == i) {
						break;
					}
				}
				cur_color++;
			}
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
	cin >> n >> m;
	tin.resize(n, -1);
	fup.resize(n, 1e9);
	color.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(0, -1);
	while (!s.empty()) {
		int x = s.top();
		color[x] = cur_color;
		s.pop();
	}
	cout << cur_color << "\n";
	for (int i = 0; i < n; i++) {
		cout << color[i] << ' ';
	}
	return 0;
}
