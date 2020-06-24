#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int K = 21;
const int INF = 1e9;

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

struct sparce_table {
	log_table log_value_table;
	int *dp[K];
	size_t sz;
	sparce_table() {}
	sparce_table(int *mas, size_t size) {
		log_value_table = log_table(size + 1);
		for (size_t i = 0; i < K; i++) {
			dp[i] = (int*)malloc(sizeof(int) * size);
			for (size_t j = 0; j < size; j++) {
				dp[i][j] = INF;
			}
		}
		for (size_t i = 0; i < size; i++) {
			dp[0][i] = mas[i];
		}
		for (size_t i = 1; i < K; i++) {
			for (size_t j = 0; j < size; j++) {
				int r = j + (1 << (i - 1));
				if (r >= (int)size) {
					break;
				}
				dp[i][j] = min(dp[i - 1][j], dp[i - 1][r]);
			}
		}
		/*for (int i = 0; i <= 3; i++) {
			for (int j = 0; j < (int)size; j++) {
				cout << "len = " << (1 << i) << ' ' << ", j = " << j << ' ' << ", dp[i][j] = " << dp[i][j] << "\n";
			}
		}*/
		sz = size;
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
		return res;
	}
};

const int N = 1e5 + 10;

int a[N];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, a1, u, v;
	cin >> n >> m >> a1 >> u >> v;
	a[0] = a1;
	for (int i = 1; i < n; i++) {
		a[i] = (23 * a[i - 1] + 21563) % 16714589;
	}
	sparce_table table = sparce_table(a, n);
	int last_ans = 0;
	int uu = 0, vv = 0;
	for (int i = 0; i < m; i++) {
		uu = u;
		vv = v;
		last_ans = table.get_min(u - 1, v - 1);
		u = (17 * u + 751 + last_ans + (i + 1) * 2);
		u %= n;
		u++;
		v = (13 * v + 593 + last_ans + (i + 1) * 5);
		v %= n;
		v++;
	}
	cout << uu << ' ' << vv << ' ' << last_ans;
	return 0;
}
