#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 3e6 + 10;

unsigned int cur = 0;
unsigned int nextRand24(uint a, uint b) {
	cur = cur * a + b;
	return (cur >> 8);
}

unsigned int nextRand32(uint a, uint b) {
	unsigned int aa = nextRand24(a, b), bb = nextRand24(a, b);
	return (aa << 8) ^ bb;
}

int a[N];

ll k;

void merge(int l, int r) {

}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n >> k;
	uint x, y;
	cin >> x >> y;
	for (int i = 0; i < n; i++){
		a[i] = nextRand32(x, y);
	}
	for (int i = 0; i < n; i++)
		cout << a[i] << ' ';
	return 0;
}