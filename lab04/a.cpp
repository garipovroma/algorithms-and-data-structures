#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

vector <vector<pair<int, int>>> p;
vector <vector<ll>> dp;
vector <vector<pair<ll, ll>>> sz;
vector <ll> a, b;

const ll INF = 1e18;

void calc(int l, int r) {
	if (dp[l][r] != INF)
		return;
	if (l == r) {
		dp[l][r] = 0;
		return;
	}
	for (int i = l; i + 1 <= r; i++) {
		calc(l, i);
		calc(i + 1, r);
		ll x = dp[l][i] + dp[i + 1][r] + sz[l][i].first * sz[l][i].second * sz[i + 1][r].second;
		if (x < dp[l][r]) {
			dp[l][r] = x;
			sz[l][r] = {sz[l][i].first, sz[i + 1][r].second};
			p[l][r] = {i, i + 1};
		}
	}
}

string get_ans(int l, int r) {
	if (l == r) return string("A");
	string res = "";
	int x = p[l][r].first;
	int y = p[l][r].second;
	string xs = get_ans(l, x);
	string ys = get_ans(y, r);
	res = "(" + xs + ys + ")";
	return res;
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("matrix.in", "rt", stdin);
	freopen("matrix.out", "wt", stdout);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	a.resize(n);
	b.resize(n);
	dp.resize(n, vector <ll> (n, INF));
	sz.resize(n, vector <pair<ll, ll>>(n, {-1, -1}));
	p.resize(n, vector<pair<int, int>> (n, {-1, -1}));
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
		sz[i][i] = {a[i], b[i]};
	}
	calc(0, n - 1);
	//  cout << dp[0][n - 1];
	string ans = get_ans(0, n - 1);
	cout << ans;
	#ifdef HOME
	cout << dp[0][n - 1];
	#endif  //  HOME
	return 0;
}

