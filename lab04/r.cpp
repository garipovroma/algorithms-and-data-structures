#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const int N = 1001;

string dp[N][N];   // sum, mod
bool was[N][N];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("number.in", "rt", stdin);
	freopen("number.out", "wt", stdout);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	dp[0][0] = "";
	queue <pair<int, int>> q;
	q.push({0, 0});
	int kk = 0;
	int keks = 0;
	while (kk < 1e6) {
		if (q.empty()) {
			break;
		}
		pair <int, int> cur = q.front();
		q.pop();
		string s = dp[cur.first][cur.second];
		s.push_back('#');
		//  cout << cur.first << ' ' << cur.second << ' ' << dp[cur.first][cur.second]
		//  << ' ' << len(q) << " : ";
		kk++;
		//  if (kk == 20) break;
		for (int i = 0; i <= 9; i++) {
			int sum = cur.first + i;
			int mod = ((cur.second * 10) + i) % n;
			if (sum > n) {
				break;
			}
			s[len(s) - 1] = char('0' + i);
			if (!was[sum][mod]) {
				//  cout << i << ' ';
				q.push({sum, mod});
				was[sum][mod] = true;
				dp[sum][mod] = s;
				keks = max(keks, len(s));
			}
		}
		//  cout << endl;
	}
	#ifdef HOME
	cout << keks << endl;
	#endif // HOME
	for (int i = 0; i <= 1000; i++) {
		if (i == 1000) 
			cout << dp[i][0];
		else
			cout << dp[i][0] << ", ";
	}
	cout << endl;
//	cout << dp[n][0];
	return 0;
}

