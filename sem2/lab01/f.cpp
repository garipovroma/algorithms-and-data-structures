#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

int getRand() {
    return (rand() >> 16) + rand();
}

struct Node {
    Node *l, *r;
    int sz;
    int x, y;
    bool full, empty;
    Node() {
        l = r = nullptr;
        full = false;
        empty = true;
    }
    Node(int a) {
        x = a;
        y = getRand();
        l = r = nullptr;
        sz = 1;
        full = false;
        empty = true;
    }
};

const int N = 1e6 + 228;

Node nodes[N];
int curPos = 0;

Node *nwNode(int x) {
    nodes[curPos] = Node(x);
    curPos++;
    return &nodes[curPos - 1];
}

bool get_full(Node *v) {
    if (v == nullptr) {
        return true;
    }
    return v->full;
}

void upd_full(Node *v) {
    if (v == nullptr) {
        return;
    }
    v->full = get_full(v->l) && get_full(v->r) && (!(v->empty));
}


int get_sz(Node *v) {
    if (v == nullptr) {
        return 0;
    }
    return v->sz;
}

void upd_sz(Node *v) {
    if (v == nullptr) {
        return;
    }
    v->sz = get_sz(v->l) + 1 + get_sz(v->r);
    upd_full(v);
}

pair <Node*, Node*> split(Node *v, int k) {   //  <=  k
    if (v == nullptr) {
        return {nullptr, nullptr};
    }
    int sz = get_sz(v->l);
    if (k < sz) {
        pair <Node*, Node*> t = split(v->l, k);
        v->l = t.second;
        upd_sz(v->l);
        return {t.first, v};
    } else {
        pair <Node*, Node*> t = split(v->r, k - sz - 1);
        v->r = t.first;
        upd_sz(v->r);\
        return {v, t.second};
    }
}

Node* merge(Node *vl, Node *vr) {
    if (vl == nullptr) {
        return vr;
    }
    if (vr == nullptr) {
        return vl;
    }
    if (vl->y > vr->y) {
        vl->r = merge(vl->r, vr);
        upd_sz(vl->r);
        return vl;
    } else {
        vr->l = merge(vl, vr->l);
        upd_sz(vr->l);
        return vr;
    }
}

Node *root = nullptr;

void push_back(int val) {
    root = merge(root, nwNode(val));
}

vector <int> ans;

void print(Node *v) {
    if (v == nullptr) {
        return;
    }
    print(v->l);
    ans.push_back(v->x);
    print(v->r);
}

void kek_push_back(int pos, int val) {
    pair <Node*, Node*> t = split(root, pos - 1);
    Node *v = t.second;
    int len = 0;
    while (true) {
        if (!get_full(v->l)) {
            v = v->l;
        } else if (v->empty) {
            len += get_sz(v->l);
            break;
        } else {
            len += get_sz(v->l) + 1;
            v = v->r;
        }
    }
    v->empty = false;
    v->full = true;
    v->x = val;
    pair <Node*, Node*> t1 = split(t.second, len);
    pair <Node*, Node*> t2 = split(t1.first, len - 1);
    t.second = merge(merge(t2.second, t2.first), t1.second);
    root = merge(t.first, t.second);
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(nullptr));    //   change me
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < N; i++) {
        push_back(-1488);
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int y = i + 1;
        kek_push_back(x, y);
    }
    print(root);
    int r = len(ans) - 1;
    for (int j = len(ans) - 1; j >= 0; j--) {
        if (ans[j] == -1488) {
            r--;
        } else {
            break;
        }
    }
    int l = 1;
    vector <int> anss;
    for (int i = l; i <= r; i++)
        anss.push_back(ans[i]);
    cout << len(anss) << "\n";
    for (int i : anss) {
        if (i == -1488) {
            cout << 0;
        } else {
            cout << i;
        }
        cout << ' ';
    }
    return 0;
}
