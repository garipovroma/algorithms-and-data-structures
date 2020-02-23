#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())

typedef vector<vector<pair<int, int>>> vvii;

vector <pair<int, int>> filter(int l, int r) {
	int n = (r - l + 1);
	int x = l;
	vector <pair<int, int>> v;
	for (int i = 0; i < n / 2; i++) {
		v.push_back({x + i, x + i + n / 2});
	}
	return v;
}

vvii betonic_sort(int l, int r) {
	if (l == r) {
		return vvii(0);
	}
	int m = (l + r) / 2;
	vvii res;
	res.push_back(filter(l, r));
	vvii v1 = betonic_sort(l, m), v2 = betonic_sort(m + 1, r);
	for (int i = 0; i < len(v2); i++) {
		for (auto j : v2[i])
			v1[i].push_back(j);
	}
	for (auto i : v1)
		res.push_back(i);
	return res;
}

vvii b_sort(int l, int r) {
	vvii res = betonic_sort(l, r);
	vector <pair<int, int>> v;
	while(l < r) {
		v.push_back({l, r});
		l++;
		r--;
	}
	res[0] = v;
	return res;
}

vvii solution(int l, int r) {
	vvii res(1);
	for (int i = l; i < r; i += 2) {
		res[0].push_back({i, i + 1});
	}
	int x = 4;
	while(x <= (r - l + 1)) {
		vvii cur;
		for (int i = l; i < r; i += x) {
			vvii v = b_sort(i, i + x - 1);
			if (cur.size() == 0) {
				for (auto j : v)
					cur.push_back(j);
			} else {
				for (int j = 0; j < len(v); j++) {
					for (auto k : v[j])
						cur[j].push_back(k);
				}
			}
		}
		for (auto j : cur)
			res.push_back(j);
		x *= 2;
	}
	return res;
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
	if (n == 1) {
		cout << 1 << ' '<< 0 << ' ' << 0;
		return 0;
	}
	int x = 1;
	while(x < n) x *= 2;
	vvii s = solution(0, x - 1);
	vvii ans;
	/*for (auto i : s) {
		for (auto j : i) {
			cout << "(" << j.first << ' ' << j.second << ") ";
		}
		cout << endl;
	}
	cout << endl;*/
	for (auto i : s) {
		vector <pair<int, int>> cur;
		for (auto j : i) {
			if (j.first < n && j.second < n)
				cur.push_back(j);
		}
		if (len(cur) > 0)
			ans.push_back(cur);
	}
	int m = 0;
	for (auto i : ans)
		m += len(i);
	cout << n << ' ' << m << ' ' << len(ans) << "\n";
	for (auto i : ans) {
		cout << len(i) << ' ';
		for (auto j : i)
			cout << j.first + 1 << ' ' << j.second + 1 << ' ';
		cout << "\n";
	}
	return 0;
}
