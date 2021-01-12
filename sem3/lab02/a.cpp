#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 3e4 + 10;

vector <int> g[N];

void bfs(int s, vector <int> &d) {
	d[s] = 0;
	queue <int> q;
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i : g[x]) {
			if (d[i] == -1) {
				d[i] = d[x] + 1;
				q.push(i);
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

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	vector <int> d(n, -1);
	bfs(0, d);
	for (int i : d)
		cout << i << ' ';
	return 0;
}

