#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

struct kek {
    int v, q;
    kek() {}
    kek(int a, int b) {
        v = a;
        q = b;
    }
};

deque <kek> h;
deque <int> q;
vector <int> pos;

void swp(int v, int p) {
    swap(h[v], h[p]);
    //  swap(h[v], h[p]);
    swap(pos[h[v].q], pos[h[p].q]);
    //  swap(q[v], q[p]);
}

void sift_up(int v) {
    while (h[(v - 1) / 2].v > h[v].v) {
        int p = (v - 1) / 2;
        if (h[v].v < h[p].v) {
            swp(v, p);
            v = p;
        }
    }
}

void sift_down(int v) {
    while (2 * v + 1 < len(h)) {
        int l = 2 * v + 1;
        int r = 2 * v + 2;
        int id = l;
        if (r < len(h) && h[r].v < h[l].v) {
            id = r;
        }
        if (h[v].v <= h[id].v) break;
        swp(v, id);
        v = id;
    }
}

void add(int val, int num) {
    h.push_back(kek(val, num));
    //  q.push_back(num);
    pos[num] = len(h) - 1;
    sift_up(len(h) - 1);
}

int extract_min() {
    int v = h[0].v;
    swp(0, len(h) - 1);
    h.pop_back();
    //  q.pop_back();
    sift_down(0);
    return v;
}

pair<int, int> extractmin() {
    int x = h[0].v;
    int y = h[0].q;
    extract_min();
    pos[y] = -2;
    return {x, y};
}

void decrease_key(int v, int val) {
    h[v].v = val;
    sift_up(v);
}

void decreasekey(int x, int v) {
    int vert = pos[x];
    if (vert < 0) return;
    decrease_key(vert, v);
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string t;
    while (cin >> t) {
        pos.push_back(-1);
        if (t == "push") {
            int x;
            cin >> x;
            add(x, len(pos) - 1);
        } else if (t == "extract-min") {
            if (h.size() == 0) {
                cout << "*\n";
            } else {
                pair <int, int> query = extractmin();
                cout << query.first << ' ' << query.second + 1 << "\n";
            }
        } else if (t == "decrease-key") {
            int x, y;
            cin >> x >> y;
            x--;
            decreasekey(x, y);
        }
    }
    return 0;
}
