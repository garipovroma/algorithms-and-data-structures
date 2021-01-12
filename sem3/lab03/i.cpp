#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

const int N = 1e6;

unordered_multiset<int> g[N];
int deg[N], rdeg[N];

void find_path(int v, vector <int> &res) {
    while (!g[v].empty()) {
        auto i = *g[v].begin();
        g[v].erase(g[v].find(i));
        find_path(i, res);
    }
    res.push_back(v);
}

unordered_map<string, int> num;
unordered_map<int, string> kek;
int p[N];
int string_num = 1;

void gen(int x, int d, int k) {
    if (x == k) {
        string cur = "";
        for (int i = 0; i < k; i++) {
            char x = (char) p[i];
            char y = '0';
            char z = (char) (x + y);
            cur.push_back(z);
        }
        string x = cur.substr(0, k - 1);
        string y = cur.substr(1, k - 1);
        if (num[x] == 0) {
            num[x] = string_num++;
            kek[num[x]] = x;
        }
        if (num[y] == 0) {
            num[y] = string_num++;
            kek[num[y]] = y;
        }
        g[num[x]].insert(num[y]);
        deg[num[x]]++;
        rdeg[num[y]]++;
    } else {
        for (int i = 0; i < d; i++) {
            p[x] = i;
            gen(x + 1, d, k);
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int d, k;
    cin >> d >> k;
    if (k == 1) {
        for (int i = 0; i < d; i++) {
            cout << i;
        }
        return 0;
    }
    gen(0, d, k);
    int start = 1;
    for (int i = 1; i < string_num; i++) {
        if (deg[i] + 1 == rdeg[i]) {
            start = i;
            break;
        }
    }
    vector <int> path;
    find_path(start, path);
    reverse(all(path));
    cout << kek[path[0]];
    for (int i = 1; i < len(path); i++) {
        cout << kek[path[i]][k - 2];
    }
    return 0;
}
