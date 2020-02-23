#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int myrand() {
	return (((rand()) >> 16) + rand());
}

const int N = 1e5 + 10;

ll a[N];

int partition(int l, int r) {
	int i = l, j = r;
	ll val = a[l + myrand() % (r - l + 1)];
	// int m = (l + r) / 2;
	// int val = a[m];
	while(true) {
		while (a[j] > val) {
			j--;
		}
		while (a[i] < val) {
			i++;
		}
		if (i < j) {
			swap(a[i], a[j]);
			i++;
			j--;
		} else {
			break;
		}
	}
	return j;
}

void qsort(int l, int r) {
	if (l >= r) return;
	int ind = partition(l, r);
	qsort(l, ind);
	qsort(ind + 1, r);
}

ll b[N], c[N], t[N];

int n, m, p;

bool check(ll x) {
	for (int i = 0; i < m; i++) {
		if (b[i] != 0) {
			a[i] = (x - c[i] - t[i]) / (b[i]);
		} else {
			a[i] = (c[i] + t[i] > x) ? 0 : 1e9;
		}
	}
	qsort(0, m - 1);
	ll count = 0;
	if (n <= m) {
		for (int i = m - 1; i >= m - n; i--) {
			if (a[i] <= 0) {
				break;
			}
			count += a[i];
		}
	} else {
		for (int i = m - 1; i >= 0; i--) {
			if (a[i] <= 0) {
				break;
			}
			count += a[i];
		}
	}
	//  cout << count << ' ' << p << endl;
	return (count < p);
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	srand(time(nullptr));
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> b[i] >> c[i] >> t[i];
	}
	cin >> n >> p;
	long long l = -1, r = 1e11;
	while (r - l > 1) {
		long long m = (l + r) / 2;
		if (check(m)) {
			l = m;
		} else {
			r = m;
		}
	}
	cout << r;
	return 0;
}
