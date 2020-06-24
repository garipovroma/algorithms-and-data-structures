#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e6;

struct next_prev_array {
    vector <string> mas;
    vector <int> next1;
    vector <int> prev1;
    vector <bool> empty;
    int size() {
        return len(mas);
    }
    void push(string x) {
        mas.push_back(x);
        empty.push_back(false);
    }
    void remove(int x) {
        empty[x] = true;
    }
    int prev(int x) {
        x--;
        while (x >= 0) {
            if (!empty[x]) {
                return x;
            }
            x--;
        }
        return -1;
    }
    int next(int x) {
        x++;
        while (x < len(mas)) {
            if (!empty[x]) {
                return x;
            }
            x++;
        }
        return -1;
    }
    string operator[](int x) {
        return mas[x];
    }
    void set(int ind, string val) {
        mas[ind] = val;
    }
};

template <typename T1, typename T2> struct hash_map {
    const unsigned int P = 571;
    static const unsigned int M = 3e6 + 7;
    vector <vector<pair<T1, pair<T2, int>>>> mas = vector<vector<pair<T1, pair<T2, int>>>>(M);
    next_prev_array arr;
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
                last_get = i.second.first;
                return true;
            }
            pos++;
        }
        return false;
    }
    bool insert(T1 key, T2 val) {
        unsigned int h = get_hash(key);
        if (contains(key)) {
            mas[h][pos].second.first = val;
            arr.set(mas[h][pos].second.second, val);
        } else {
            mas[h].push_back({key, {val, arr.size()}});
            arr.push(val);
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
            pair <T1, pair<T2, int>> cur = *it;
            if (cur.first == key) {
                break;
            }
            it++;
        }
        pair <T1, pair<T2, int>> cur = *it;
        int x = cur.second.second;
        arr.remove(x);
        mas[h].erase(it);
        return true;
    }
    int get_pos(T1 key) {
        unsigned int h = get_hash(key);
        auto it = mas[h].begin();
        while (true) {
            pair <T1, pair<T2, int>> cur = *it;
            if (cur.first == key) {
                break;
            }
            it++;
        }
        pair <T1, pair<T2, int>> cur = *it;
        return cur.second.second;
    }

    string next(string s) {
        int x = get_pos(s);
        int y = arr.next(x);
        if (y == -1) {
            return "none";
        } else {
            return arr[y];
        }
    }
    string prev(string s) {
        int x = get_pos(s);
        int y = arr.prev(x);
        if (y == -1) {
            return "none";
        } else {
            return arr[y];
        }
    }
};

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("linkedmap.in", "rt", stdin);
	freopen("linkedmap.out", "wt", stdout);
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
        } else if (s == "prev") {
            string a;
            cin >> a;
            if (!v.contains(a)) {
                cout << "none\n";
                continue;
            }
            cout << v.prev(a) << "\n";
        } else if (s == "next") {
            string a;
            cin >> a;
            if (!v.contains(a)) {
                cout << "none\n";
                continue;
            }
            cout << v.next(a) << "\n";
        }
    }
    return 0;
}
