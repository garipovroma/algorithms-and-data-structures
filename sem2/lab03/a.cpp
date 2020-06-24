#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = (1 << 24) + 10;

unsigned int a_, b_;
unsigned int cur_ = 0;
unsigned int nextRand() {
	cur_ = cur_ * a_ + b_;
	return (cur_ >> 8);
}

unsigned int mas[N];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	  // build(1, 0, N - 1);
	int m, q;
	cin >> m >> q >> a_ >> b_;
	for (int i = 0; i < m; i++) {
		int dx = nextRand();
		int l = nextRand();
		int r = nextRand();
		if (l > r) swap(l, r);
		mas[l] += dx;
		mas[r + 1] -= dx;
	}
	for (int i = 1; i < N; i++) {
		mas[i] += mas[i - 1];
	}
	for (int i = 1; i < N; i++) {
		mas[i] += mas[i - 1];
	}
	unsigned int ans = 0;
	for (int i = 0; i < q; i++) {
		int l = nextRand();
		int r = nextRand();
		if (l > r) swap(l, r);
		ans = (ans + (l == 0 ? mas[r] : (mas[r] - mas[l - 1])));
	}
	cout << ans;
	return 0;
}
