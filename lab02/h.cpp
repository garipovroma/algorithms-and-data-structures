#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())

typedef long long ll;

vector <int> buf;

ll ans = 0;

void mergesort(int l, int r, vector <int> &a) {
	if (l == r) {
		return;
	}
    if (l == 0 && r == len(a) - 1) {
        buf.resize(len(a));
    }
    int m = (l + r) / 2;
    mergesort(l, m, a);
    mergesort(m + 1, r, a);
    int i = l, j = m + 1;
    for (int pos = l; pos <= r; pos++) {
        if (j == r + 1 || (i <= m && a[i] <= a[j])) {
            buf[pos] = a[i++];
        } else {
        	ans += (m - i + 1);
            buf[pos] = a[j++];
        }
    }
    for (int k = l; k <= r; k++)
        a[k] = buf[k];
}

unsigned int cur = 0;

unsigned int nextRand24(int a, int b) {
	cur = cur * a + b;
	return (cur >> 8);
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
    int a, b;
    cin >> a >> b;
    vector <int> v(n);
    for (int i = 0; i < n; i++) {
    	v[i] = nextRand24(a, b) % m;
    }
    mergesort(0, n - 1, v);
    cout << ans;
    return 0;
}
