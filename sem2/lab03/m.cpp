#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int K = 25;
const int INF = 1e9;
const int N = 1e5 + 10;

struct log_table {
	size_t sz;
	int *mas;
	log_table() {}
	log_table(size_t s) {
		mas = (int*)malloc(sizeof(int) * (s));
		mas[1] = 0;
		mas[2] = 1;
		sz = s;
		for (size_t i = 3; i < s; i++) {
			mas[i] = mas[i / 2] + 1;
		}
	}
	int get(size_t ind) {
		return mas[ind];
	}
	size_t size() {
		return sz;
	}
	void print_all() {
		for (size_t i = 0; i < sz; i++) {
			cout << i << " : " << mas[i] << "\n";
		}
	}
};

struct sparse_table {
	log_table log_value_table;
	int *dp[K];
	int *id[K];
	size_t sz;
	sparse_table() {}
	sparse_table(int *mas, size_t size) {
		log_value_table = log_table(size + 1);
		for (size_t i = 0; i < K; i++) {
			dp[i] = (int*)malloc(sizeof(int) * size);
			id[i] = (int*)malloc(sizeof(int) * size);
			for (size_t j = 0; j < size; j++) {
				dp[i][j] = INF;
				id[i][j] = INF;
			}
		}
		for (size_t i = 0; i < size; i++) {
			dp[0][i] = mas[i];
			id[0][i] = i;
		}
		for (size_t i = 1; i < K; i++) {
			for (size_t j = 0; j < size; j++) {
				int r = j + (1 << (i - 1));
				if (r >= (int)size) {
					break;
				}
				dp[i][j] = min(dp[i - 1][j], dp[i - 1][r]);
				if (dp[i][j] == dp[i - 1][j]) {
					id[i][j] = id[i - 1][j];
				} else {
					id[i][j] = id[i - 1][r];
				}
			}
		}
		/*for (int i = 0; i <= 3; i++) {
			for (int j = 0; j < (int)size; j++) {
				cout << "len = " << (1 << i) << ' ' << ", j = " << j << ' ' << ", dp[i][j] = " << dp[i][j] << "\n";
			}
		}*/
		sz = size;
	}
	int last_id = INF;
	int get_last_query_pos() {
		return last_id;
	}
	int get_min(int l, int r) {
		if (l > r) {
			swap(l, r);
		}
		int len = (r - l + 1);
		int len_log = log_value_table.get(len);
		int v1 = dp[len_log][l];
		int pos = r - (1 << len_log) + 1;
		int v2 = dp[len_log][pos];
		int res = min(v1, v2);
		if (res == v1) {
			last_id = id[len_log][l];
		} else {
			last_id = id[len_log][pos];
		}
		return res;
	}
};

vector <int> depth_mas;
vector <int> ord_mas;
vector <int> g[N];
int ls[N], rs[N];

void dfs(int v, int depth, int anc) {
	ls[v] = len(depth_mas);
	depth_mas.push_back(depth);
	ord_mas.push_back(v);
	for (int i : g[v]) {
		if (i != anc) {
			depth_mas.push_back(depth);
			ord_mas.push_back(v);
			dfs(i, depth + 1, v);
		}
	}
	if (g[v].size() == 0) {
		depth_mas.push_back(depth);
		ord_mas.push_back(v);
	}
	rs[v] = len(depth_mas) - 1;
}

int buf[10 * N];
const int M = 10;
ll q[M];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n, m;
	cin >> n >> m;
	for (int i = 1; i <= n - 1; i++) {
		int x;
		cin >> x;
		g[i].push_back(x);
		g[x].push_back(i);
	}
	dfs(0, 1, -1);
	/*for (int i = 0; i < len(depth_mas); i++) {
		cout << ord_mas[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++) {и
		cout << i << ' ' << ls[i] << ' ' << rs[i] << "\n";
	}*/
	for (int i = 0; i < len(depth_mas); i++) {
		buf[i] = depth_mas[i];
	}
	sparse_table table = sparse_table(buf, len(depth_mas));
	ll a1, a2, x, y, z;
	cin >> a1 >> a2 >> x >> y >> z;
	q[0] = a1;
	q[1] = a2;
	ll was = 0;
	ll ans = 0;
	for (int i = 0; i < m; i++) {
		ll v = 0, u = 0;
		if (i != 0) {
			ll curx = (x * q[(2 * i - 2 + M) % M] + y * q[(2 * i - 1 + M) % M] + z) % n;
			q[(2 * i) % M] = curx;
			ll cury = (x * q[(2 * i - 1 + M) % M] + y * q[(2 * i + M) % M] + z) % n;
			q[(2 * i + 1) % M] = cury;
			v = (curx + was) % n;
			u = cury;
		} else {
			v = q[0];
			u = q[1];
		}
		ll l1 = ls[v];
		ll r1 = rs[v];
		ll l2 = ls[u];
		ll r2 = rs[u];
		ll l = min((int)l1, (int)l2);
		ll r = max((int)r1, (int)r2);
		ll mn = table.get_min((int)l, (int)r);
		mn ^= mn;
		ll pos = table.get_last_query_pos();
		ll res = ord_mas[(int)pos];
		was = res;
		ans += 1ll * res;
		//  cout << v << ' ' << u << ' ' << res << "\n";
	}
	cout << ans;
	return 0;
}

