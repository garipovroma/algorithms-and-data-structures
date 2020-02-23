#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

int lowerBound(vector <int> &a, int x) {
	int l = 0, r = len(a) - 1;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (a[m] < x)
			l = m;
		else
			r = m;
	}
	if (a[l] >= x)
		r = l;
	return r;
}

int upperBound(vector <int> &a, int x) {
	int l = 0, r = len(a) - 1;
	while(r - l > 1) {
		int m = (l + r) / 2;
		if (a[m] <= x)
			l = m;
		else
			r = m;
	}
	if (a[r] <= x) r++;
	return r;
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		int l = lowerBound(a, x);
		int r = upperBound(a, x);
		if (a[l] != x) {
			cout << "-1 -1\n";
		} else {
			cout << l + 1 << ' ' << r << "\n";
		}
	}
	return 0;
}
