#include <iostream>
#include <vector>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;


struct hash_table {  //  use this hash_table only with ints and strings
    unsigned int P = 59;
    unsigned int M = 150;
    vector <vector<string>> mas = vector<vector<string>>(M);
    int sz = 0;
    hash_table() {}
    hash_table(const hash_table &a) {
        mas = a.mas;
        sz = a.sz;
    }
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
    bool contains(string val) {
        unsigned int h = get_hash(val);
        for (auto i : mas[h]) {
            if (i == val) {
                return true;
            }
        }
        return false;
    }
    bool insert(string val) {
        if (contains(val)) {
            return false;
        }
        unsigned int h = get_hash(val);
        mas[h].push_back(val);
        sz++;
        return true;
    }
    int size() {
        return sz;
    }
    bool erase(string val) {
        if (!contains(val)) {
            return false;
        }
        unsigned int h = get_hash(val);
        auto it = mas[h].begin();
        while (*it != val) {
            it++;
        }
        mas[h].erase(it);
        sz--;
        return true;
    }
    void get_all() {
        for (int i = 0; i < int(M); i++) {
            for (int j = 0; j < len(mas[i]); j++) {
                cout << mas[i][j] << ' ';
            }
        }
    }
    hash_table(string &s) {
        insert(s);
    }
};


const int N = 1e6 + 227;

struct hash_map {
    int M = 1e6 + 227;
    int P = 571;
    vector<pair<string, hash_table>> mas[N];
    hash_table last_get;
    unsigned int h;
    int pos = 0;
    unsigned int get_hash(string &s) {
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
    bool contains(string &key, unsigned int h, bool need) {
        pos = 0;
        for (int i = 0; i < len(mas[h]); i++) {
            if (mas[h][i].first == key && mas[h][i].second.size() != 0) {
                if (need) {
                   last_get = mas[h][i].second;
                }
                return true;
            }
            pos++;
        }
        return false;
    }
    bool insert(string &key, string &val) {
        unsigned int h = get_hash(key);
        if (contains(key, h, false)) {
            mas[h][pos].second.insert(val);
        } else {
            mas[h].push_back({key, hash_table(val)});
        }
        return true;
    }
    bool erase_single(string &key, string &value) {
        unsigned int h = get_hash(key);
        if (!contains(key, h, false)) {
            return false;
        }
        auto it = mas[h].begin();
        while (true) {
            if (it->first == key && it->second.size() != 0) {
                break;
            }
            it++;
        }
        it->second.erase(value);
        return true;
    }
    bool erase_all(string val) {
        unsigned int h = get_hash(val);
        if (!contains(val, h, false)) {
            return false;
        }
        int ind = 0;
        for (int i = 0; i < len(mas[h]); i++) {
            if (mas[h][i].first == val && mas[h][i].second.size() != 0) {
                ind = i;
                break;
            }
        }
        mas[h][ind].second = hash_table();
        return true;
    }
};

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("multimap.in", "rt", stdin);
    freopen("multimap.out", "wt", stdout);
#endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    hash_map v;
    while (cin >> s) {
        if (s == "put") {
            string a, b;
            cin >> a >> b;
            v.insert(a, b);
        } else if (s == "get") {
            string a;
            cin >> a;
            unsigned int h = v.get_hash(a);
            if (v.contains(a, h, true)) {
                cout << v.last_get.sz << " ";
                v.last_get.get_all();
                cout << "\n";
            } else {
                cout << "0\n";
            }
        } else if (s == "delete") {
            string a, b;
            cin >> a >> b;
            v.erase_single(a, b);
        } else if (s == "deleteall") {
            string a;
            cin >> a;
            v.erase_all(a);
        }
    }
    return 0;
}
