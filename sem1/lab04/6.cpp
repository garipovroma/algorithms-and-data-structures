#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("vectors.in", "rt", stdin);
	freopen("vectors.out", "wt", stdout);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < (1 << n); i++) {
		vector <int> cur;
		for (int j = n - 1; j >= 0; j--) {
			int b = (i >> j) & 1;
			cur.push_back(b);
		}
		bool ok = true;
		for (int x = 0; x < len(cur) - 1; x++) {
			if (cur[x] == '1' && cur[x + 1] == '1')
				ok = false;
		}
		if (ok) {
			for (auto x : cur)
				cout << x;
			cout << "\n";
		}
	}
	return 0;
}
