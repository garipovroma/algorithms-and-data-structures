#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5 + 10;
const int INF = 1000000000;

vector <pair<int, int>> g[N];
vector <int> used;
vector <int> ord;
vector <int> dp;

void tops(int v) {
	used[v] = 1;
	for (auto i : g[v]) {
		if (used[i.first] == 0) {
			tops(i.first);
		}
	}
	ord.push_back(v);
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	s--;
	t--;
	dp.resize(n, INF);
	used.resize(n, 0);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		g[a].push_back({b, c});
	}
	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			tops(i);
		}
	}
	reverse(all(ord));
	dp[s] = 0;
	int pos = 0;
	for (int i = 0; i < n; i++) {
		if (ord[i] == s) {
			pos = i;
			break;
		}
	}
	for (int i = pos; i < n; i++) {
		int v = ord[i];
		if (dp[v] == INF) {
			continue;
		}
		for (auto j : g[v]) {
			dp[j.first] = min(dp[j.first], dp[v] + j.second);
		}
	}
	if (dp[t] == INF) {
		cout << "Unreachable";
	} else {
		cout << dp[t];
	}
	return 0;
}
