#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

template <typename T1, typename T2> struct hash_map {
	const unsigned int P = 571;
	static const unsigned int M = 3e6 + 7;
	vector <vector<pair<T1, T2>>> mas = vector<vector<pair<T1, T2>>>(M);
	unsigned int get_hash(string s) {
		unsigned int res = 0;
		for (int i = 0; i < len(s); i++) {
			res = res * P + s[i];
			res %= M;
		}
		return res;
	}
	unsigned int get_hash(int x) {
		return x % M;
	}
	int pos;
	T2 last_get;
	bool contains(T1 key) {
		unsigned int h = get_hash(key);
		pos = 0;
		for (auto i : mas[h]) {
			if (i.first == key) {
				last_get = i.second;
				return true;
			}
			pos++;
		}
		return false;
	}
	bool insert(T1 key, T2 val) {
		unsigned int h = get_hash(key);
		if (contains(key)) {
			mas[h][pos].second = val;
		} else {
			mas[h].push_back({key, val});
		}
		return true;
	}
	bool erase(T1 key) {
		if (!contains(key)) {
			return false;
		}
		unsigned int h = get_hash(key);
		auto it = mas[h].begin();
		while (true) {
			pair <T1, T2> cur = *it;
			if (cur.first == key) {
				break;
			}
			it++;
		}
		mas[h].erase(it);
		return true;
	}
};

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("map.in", "rt", stdin);
	freopen("map.out", "wt", stdout);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	hash_map <string, string> v;
	while (cin >> s) {
		if (s == "put") {
			string a, b;
			cin >> a >> b;
			v.insert(a, b);
		} else if (s == "get") {
			string a;
			cin >> a;
			if (v.contains(a)) {
				cout << v.last_get << "\n";
			} else {
				cout << "none\n";
			}
		} else if (s == "delete") {
			string a;
			cin >> a;
			v.erase(a);
		}
	}
	return 0;
}
