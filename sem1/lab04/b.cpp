#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("lis.in", "rt", stdin);
	freopen("lis.out", "wt", stdout);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector <int> w(n + 1, 2e9 + 10);
	w[0] = -2e9;
	vector <int> p(n + 1, -1), pp(n + 1, -1);
	for (int i = 0; i < n; i++) {
		int x = upper_bound(all(w), a[i]) - w.begin();
		if (w[x - 1] < a[i] && a[i] < w[x]) {
			p[x] = i;
			pp[i] = p[x - 1];
			w[x] = a[i];
		}
	}
	int ans = -1;
	for (int i = 0; i <= n; i++) {
		if (w[i] != 2e9 + 10)
			ans = i;
	}
	cout << ans << endl;
	int kekus = p[ans];
	vector <int> lis;
	while (kekus != -1) {
		lis.push_back(a[kekus]);
		kekus = pp[kekus];
	}
	reverse(all(lis));
	for (int i : lis)
		cout << i << ' ';
	return 0;
}
