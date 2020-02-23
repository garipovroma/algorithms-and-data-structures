#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const int N = 151;

int x, a, y, b, l;
int dp[N][N][N];   //    row_num,

bool check(int v) {

}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("bridge.in", "rt", stdin);
	freopen("bridge.out", "wt", stdout);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> x >> a >> y >> b >> l;
	int left = 0, right = 2000;
	while (right - left > 1) {
		int middle = (left + right) / 2;
		if (check(middle))
			l = m;
		else
			r = m;
	}
	cout << l;
	return 0;
}

