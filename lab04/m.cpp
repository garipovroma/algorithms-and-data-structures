#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const int N = 19;
const ll INF = 1e18;

bool go[N][N];
ll c[N][N];

ll dp[1 << N][N];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("salesman.in", "rt", stdin);
	freopen("salesman.out", "wt", stdout);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		a--;
		b--;
		go[a][b] = true;
		go[b][a] = true;
		c[a][b] = cost;
		c[b][a] = cost;
	}
	for (int msk = 0; msk < (1 << n); msk++) {
		for (int i = 0; i < n; i++)
			dp[msk][i] = INF;
	}
	for (int i = 0; i < n; i++) {
		int x = (1 << i);
		dp[x][i] = 0;
	}
	for (int msk = 1; msk < (1 << n); msk++) {
		for (int beg = 0; beg < n; beg++) {
			int b = (msk >> beg) & 1;
			if (b == 0) {
				continue;
			}
			for (int end = 0; end < n; end++) {
				int bb = (msk >> end) & 1;
				if (bb == 1) {
					continue;
				}
				if (end == beg) {
					continue;
				}
				if (!go[end][beg]) continue;
				int kek = (msk ^ (1 << end));
				dp[kek][end] = min(dp[kek][end], dp[msk][beg] + c[beg][end]);
			}
		}
	}
	ll ans = INF;
	int MSK = (1 << n) - 1;
	for (int i = 0; i < n; i++) {
		ans = min(ans, dp[MSK][i]);
	}
	if (ans == INF) {
		ans = -1;
	}
	cout << ans;
	return 0;
}

