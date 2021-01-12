#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;
namespace std {
    template<>
    struct hash<std::pair<int, int>> {
        inline size_t operator()(const std::pair<int, int>& v) const {
            std::hash<int> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

const int N = 80010;

vector <pair<int, int>> edges;
unordered_multiset<int> g[N];
vector <int> path, deg;

void find_path(int v, vector <int> &res) {
    while (!g[v].empty()) {
        auto i = *g[v].begin();
        g[v].erase(g[v].find(i));
        g[i].erase(g[i].find(v));
        find_path(i, res);
    }
    res.push_back(v);
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
    deg.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].insert(b);
        g[b].insert(a);
        deg[a]++;
        deg[b]++;
        edges.emplace_back(a, b);
        edges.emplace_back(b, a);
    }
    unordered_multiset<pair<int, int>> new_edges;
    vector <int> odd;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 1) {
            odd.push_back(i);
        }
    }
    int start = (odd.empty() ? 0 : odd[0]);
    for (int i = 0; i < len(odd); i += 2) {
        int x = odd[i];
        int y = odd[i + 1];
        g[x].insert(y);
        g[y].insert(x);
        new_edges.insert({x, y});
        new_edges.insert({y, x});
    }
    find_path(start, path);
    reverse(all(path));
    vector <vector<int>> ans(1, vector<int>(1, path[0]));
    for (int i = 0; i < len(path) - 1; i++) {
        int x = path[i];
        int y = path[i + 1];
        if (new_edges.find({x, y}) != new_edges.end()) {
            ans.emplace_back(1, y);
            new_edges.erase(new_edges.find({x, y}));
            new_edges.erase(new_edges.find({y, x}));
        } else {
            ans.back().push_back(y);
        }
    }
    if (len(ans) > 1) {
        reverse(all(ans[0]));
        for (int i = len(ans.back()) - 2; i >= 0; i--) {
            ans[0].push_back(ans.back()[i]);
        }
        reverse(all(ans[0]));
        ans.pop_back();
    }
    cout << len(ans) << "\n";
    for (auto i : ans) {
        for (auto j : i) {
            cout << j + 1 << ' ';
        }
        cout << "\n";
    }
    return 0;
}
