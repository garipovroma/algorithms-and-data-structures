#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 50;
const int CN = 6 * N;
const int INF = 1000000000;

int n, m;

vector <int> g[CN];
vector <pair<int, int>> edges;

set <int> intersect(set <int> &s1, set <int> &s2) {
    set<int> intersection;
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(), std::inserter(intersection, intersection.begin()));
    return intersection;
}

set <int> unionn(set <int> &s1, set <int> &s2) {
    set<int> result = s1;
    for (int i : s2) {
        result.insert(i);
    }
    return result;
}

set <int> diff(set<int> &s1, set<int> &s2) {
    std::set<int> result;
    std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),
                        std::inserter(result, result.end()));
    return result;
}

vector <int> color;

void dfs(int v, int u) {
    color[v] = u;
    for (int i : g[v]) {
        if (color[i] == -1) {
            dfs(i, 1 - u);
        }
    }
}

vector <int> ans;
int ans_colors = INF;
int cur_colors = -1;

bool check() {
    for (int i = 0; i < m; i++) {
        for (int j : g[i]) {
            if (color[i] == color[j]) {
                return false;
            }
        }
    }
    if (ans_colors > cur_colors) {
        ans_colors = cur_colors;
        for (int i = 0; i < m; i++) {
            ans[i] = color[i];
        }
    }
    return true;
}

bool f(set <int> &A, set <int> &I) {
    if (clock() > CLOCKS_PER_SEC * 0.9) {
        return true;
    }
    if (len(A) == 0) {
        for (int i = 0; i < m; i++) {
            color[i] = -1;
        }
        cur_colors = 2;
        for (int i = 0; i < m; i++) {
            if (color[i] == -1) {
                dfs(i, 0);
            }
        }
        check();
        cur_colors = 3;
        for (int i = 0; i < m; i++) {
            color[i] = -1;
        }
        for (int i : I) {
            color[i] = 2;
        }
        for (int i = 0; i < m; i++) {
            if (color[i] == -1) {
                dfs(i, 0);
            }
        }
        check();
        return false;
    }
    int vert = -1;
    int sz = INF;
    set <int> s;
    for (int x : A) {
        int sum = 0;
        for (int i : g[x]) {
            if (A.find(i) != A.end()) {
                sum++;
            }
        }

        if (sum < sz) {
            vert = x;
            sz = sum;
        }
    }
    for (int i : g[vert]) {
        if (A.find(i) != A.end()) {
            s.insert(i);
        }
    }
    set <int> kek = intersect(s, A);
    kek.insert(vert);
    for (int i : kek) {
        set <int> neig;
        for (int j : g[i]) {
            neig.insert(j);
        }
        set <int> new_A = diff(A, neig);
        if (new_A.find(i) != new_A.end()) {
            new_A.erase(i);
        }
        set <int> new_I = I;
        new_I.insert(i);
        f(new_A, new_I);
    }
    return false;
}

void solve() {
    for (int i = 0; i < len(edges); i++) {
        g[edges[i].first].push_back(edges[i].second);
        g[edges[i].second].push_back(edges[i].first);
    }
    set <int> A;
    for (int i = 0; i < m; i++) {
        A.insert(i);
    }
    set <int> I;
    ans.resize(m);
    color.resize(m, 0);
    cur_colors = 1;
    if (check()) {
        ans = color;
        return;
    }
    f(A, I);
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
    }
    vector <pair<int, int>> new_edges;
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            int x = edges[i].first, y = edges[i].second;
            int v = edges[j].first, u = edges[j].second;
            if (x > y) {
                swap(x, y);
            }
            if (v > u) {
                swap(v, u);
            }
            if (x == v || x == u || y == v || y == u) {
                new_edges.push_back({i, j});
            }
        }
    }
    edges = new_edges;
    solve();
    if (ans_colors == INF) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < m; i++) {
        cout << ans[i] + 1 << ' ';
    }
    return 0;
} 
