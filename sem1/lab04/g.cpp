#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

struct meet {
	int a, b, c;
	meet() {}
	meet(int _a, int _b, int _c) {
		a = _a;
		b = _b;
		c = _c;
	}
};

const int N = 20;
const int MSK = (1 << 20) + 1;

meet m[N];
int changex[MSK];
bool ok[MSK];
int parent[MSK];
int kek[MSK];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("meetings.in", "rt", stdin);
	freopen("meetings.out", "wt", stdout);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		m[i] = meet(a, b, c);
	}
	for (int msk = 0; msk < (1 << n); msk++) {
		ok[msk] = false;
		changex[msk] = 0;
		for (int i = 0; i < n; i++) {
			int b = (msk >> i) & 1;
			if (b == 1)
				changex[msk] = changex[msk] + m[i].c;
		}
	}
	parent[0] = -1;
	ok[0] = true;
	for (int msk = 0; msk < (1 << n); msk++) {
		if (!ok[msk]) {
			continue;
		}
		for (int i = 0; i < n; i++) {
			int b = (msk >> i) & 1;
			if (b == 1) {
				continue;
			}
			int l = m[i].a;
			int r = m[i].b;
			int nw_msk = (msk + (1 << i));
			if (l <= k + changex[msk] && k + changex[msk] <= r) {
				ok[nw_msk] = true;
				parent[nw_msk] = msk;
				kek[nw_msk] = i;
			}
		}
	}
	int mx = -1, pos = -1;
	for (int msk = 0; msk < (1 << n); msk++) {
		if (!ok[msk]) {
			continue;
		}
		int count = 0;
		for (int i = 0; i < n; i++) {
			int b = (msk >> i) & 1;
			count += b;
		}
		if (count > mx) {
			mx = count;
			pos = msk;
		}
	}
	vector <int> ans;
	while (parent[pos] != -1) {
		ans.push_back(kek[pos]);
		pos = parent[pos];
	}
	reverse(all(ans));
	cout << len(ans) << "\n";
	for (auto i : ans)
		cout << i + 1  << ' ';
	return 0;
}

