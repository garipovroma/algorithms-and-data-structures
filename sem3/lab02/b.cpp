#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 2e3 + 10;
const ll INF = 1000000000000000000;

ll g[N][N];

void dijkstra(int s, int n, vector <ll> &d) {
	d[s] = 0;
	vector <bool> was(n, false);
	for (int i = 0; i < n; i++) {
		int v = -1;
		for (int j = 0; j < n; j++) {
			if (!was[j] && (v == -1 || d[j] < d[v])) {
				v = j;
			}
		}
		if (v == -1) {
			break;
		}
		was[v] = true;
		for (int j = 0; j < n; j++) {
			if (g[v][j] == -1) {
				continue;
			}
			if (d[j] > d[v] + g[v][j]) {
				d[j] = d[v] + g[v][j];
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

	int n, s, f;
	cin >> n >> s >> f;
	s--;
	f--;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> g[i][j];
		}
	}

	vector <ll> d(n, INF);
	dijkstra(s, n, d);
	if (d[f] == INF) {
		d[f] = -1;
	}
	cout << d[f];
	return 0;
}
