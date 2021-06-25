#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1000;
const int CN = 6 * N;

int n, m;

vector <int> inG[N];
vector <int> g[CN];
vector <int> tg[CN];
string colors;

vector <int> used;
vector <int> ord;

void tops(int v) {
    used[v] = 1;
    for (int i : g[v]) {
        if (used[i] == 0) {
            tops(i);
        }
    }
    ord.push_back(v);
}

int get_vert(int v, int color, int neg) {
    return n * color + v + (neg == 1 ? CN / 2 : 0);
}

void add_term(int x, int x_col, int x_neg, int y, int y_col, int y_neg) {
    int xx0 = get_vert(x, x_col, 1 - x_neg);
    int yy0 = get_vert(y, y_col, 0 + y_neg);
    int xx1 = get_vert(y, y_col, 1 - y_neg);
    int yy1 = get_vert(x, x_col, 0 + x_neg);
    g[xx0].push_back(yy0);
    g[xx1].push_back(yy1);
}

int next_col(int col) {
    return (col + 1) % 3;
}

int prev_col(int col) {
    return (col + 2) % 3;
}

vector <int> sat_color;
int cur_sat_color = 1;

void sat_dfs(int v) {
    sat_color[v] = cur_sat_color;
    for (int i : tg[v]) {
        if (sat_color[i] == 0) {
            sat_dfs(i);
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
    cin >> n >> m >> colors;
    vector <int> colors_vec(n);
    int new_n = CN;
    for (int i = 0; i < n; i++) {
        if (colors[i] == 'R') {
            colors_vec[i] = 0;
        } else if (colors[i] == 'G') {
            colors_vec[i] = 1;
        } else if (colors[i] == 'B') {
            colors_vec[i] = 2;
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        inG[a].push_back(b);
        inG[b].push_back(a);
        int col_a = colors_vec[a];
        int col_b = colors_vec[b];
        if (col_a == col_b) {
            add_term(a, prev_col(col_a), 1, b, prev_col(col_b), 1);
            add_term(a, next_col(col_a), 1, b, next_col(col_b), 1);
        } else {
            int missed_col = -1;
            for (int j = 0; j < 3; j++) {
                if (j == col_a || j == col_b) {
                    continue;
                }
                missed_col = j;
            }
            add_term(a, missed_col, 1, b, missed_col, 1);
        }
    }
    for (int a = 0; a < n; a++) {
        int col = colors_vec[a];
        add_term(a, col, 1, a, col, 1);
        add_term(a, next_col(col), 0, a, prev_col(col), 0);
        add_term(a, next_col(col), 1, a, prev_col(col), 1);
    }

//    int sum = 0;

    for (int i = 0; i < new_n; i++) {
//        cout << i << " : ";
        for (int j : g[i]) {
//            cout << j << ' ';
            tg[j].push_back(i);
        }
//        cout << "\n";
//        sum += len(g[i]);
    }
//    cout << sum << "\n";

    used.resize(new_n, 0);
    for (int i = 0; i < new_n; i++) {
        if (used[i] == 0) {
            tops(i);
        }
    }
    reverse(all(ord));

    sat_color.resize(new_n, 0);
    for (int i : ord) {
        if (sat_color[i] == 0) {
            sat_dfs(i);
            cur_sat_color++;
        }
    }

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cout << i << ' ' << j << ' ' << 0 << " : " << sat_color[get_vert(i, j, 0)] << "\n";
            cout << i << ' ' << j << ' ' << 1 << " : " << sat_color[get_vert(i, j, 1)] << "\n";
        }
    }
*/
    bool problem = false;
    vector <int> ans_color;
    for (int i = 0; i < n; i++) {
        int suitable_color = -1;
        int suitable_count = 0;
        for (int j = 0; j < 3; j++) {
            int x = get_vert(i, j, 0);
            int y = get_vert(i, j, 1);
            if (sat_color[x] != sat_color[y]) {
                if (sat_color[x] > sat_color[y]) {
                    suitable_color = j;
                    suitable_count++;
                }
            }
        }
        if (suitable_count == 0) {
            problem = true;
        } else if (suitable_count == 1) {
            ans_color.push_back(suitable_color);
        } else {
            ans_color.push_back(1000000000);
        }
//        cout << suitable_count << ' ' << suitable_color << "\n";
    }
//    cout << "\n";
    if (problem) {
        cout << "Impossible";
    } else {
        /*for (int i : ans_color) {
            cout << i << ' ';
        }
        cout << "\n";
         */
        for (int i : ans_color) {
            if (i == 0) {
                cout << "R";
            } else if (i == 1) {
                cout << "G";
            } else if (i == 2) {
                cout << "B";
            }
        }
    }
    return 0;
} 
