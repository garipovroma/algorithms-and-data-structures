#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

int myRand() {
    return ((rand() >> 16) + rand());
}

struct Node {
    int x, y, sz;
    Node *l, *r;
    Node() {
        l = r = nullptr;
        sz = 1;
        y = myRand();
    }
    Node(int a) {
        x = a;
        y = myRand();
        sz = 1;
        l = r = nullptr;
    }
};

const int N = 1e6 + 228;
Node v[N];
int curPos = 0;

Node *nwNode(int x) {
    v[curPos] = Node(x);
    curPos++;
    return &v[curPos - 1];
}

int get_sz(Node *v) {
    if (v == nullptr)
        return 0;
    else
        return v->sz;
}

void upd_sz(Node *v) {
    if (v == nullptr) {
        return;
    }
    v->sz = get_sz(v->l) + get_sz(v->r) + 1;
}

pair <Node*, Node*> split(Node *v, int k) {  // < k
    if (v == nullptr) {
        return {nullptr, nullptr};
    }
    if (k <= v->x) {
        pair <Node*, Node*> t = split(v->l, k);
        v->l = t.second;
        upd_sz(v->l);
        return {t.first, v};
    } else {
        pair <Node*, Node*> t = split(v->r, k);
        v->r = t.first;
        upd_sz(v->r);
        return {v, t.second};
    }
}

Node *merge(Node *vl, Node *vr) {
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

Node *add(int val) {
    if (curPos == 0) {
        root = nwNode(val);
        return root;
    }
    pair <Node*, Node*> curSplit = split(root, val);
    curSplit.first = merge(curSplit.first, nwNode(val));
    root = merge(curSplit.first, curSplit.second);
    return root;
}

Node *find(Node *v, int val) {
    if (v == nullptr) {
        return nullptr;
    }
    if (v->x == val) {
        return v;
    }
    if (v->x > val) {
        return find(v->l, val);
    } else {
        return find(v->r, val);
    }
}

bool containsValue(int x) {
    return (find(root, x) != nullptr);
}

bool remove(Node *&v, int val) {
    bool res = false;
    if (v->x == val) {
        v = merge(v->l, v->r);
        upd_sz(v);
        res = true;
    } else if (v->x > val) {
        res = remove(v->l, val);
        upd_sz(v);
    } else {
        res = remove(v->r, val);
        upd_sz(v);
    }
    upd_sz(v);
    return res;
}

bool remove(int val) {
    return remove(root, val);
}

void print(Node *v, string s) {
    if (v == nullptr) {
        return;
    }
    print(v->l, s + "## ");
    cout << s << v->x << endl;
    print(v->r, s + "## ");
}

int next(int x) {
    pair <Node*, Node*> t = split(root, x + 1);
    Node *v = t.second;
    int val = 1e9 + 1;
    while (v != nullptr) {
        val = v->x;
        v = v->l;
    }
    root = merge(t.first, t.second);
    return val;
}

int prev(int x) {
    pair <Node*, Node*> t = split(root, x);
    Node *v = t.first;
    int val = 1e9 + 1;
    while (v != nullptr) {
        val = v->x;
        v = v->r;
    }
    root = merge(t.first, t.second);
    return val;
}

/*
 *
 *
insert 2
insert 5
insert 3
exists 2
exists 4
next 4
prev 4
delete 5
next 4
prev 4
 */

int get_kth(Node *v, int k) {
    //   cout << v->x << ' ';
    int x = get_sz(v->l);
    if (x + 1 == k) {
        return v->x;
    } else if (x + 1 > k) {
        return get_kth(v->l, k);
    } else {
        return get_kth(v->r, k - x - 1);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   //   HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(nullptr));
    int m;
    cin >> m;
    int cursz = 0;
    for (int i = 0; i < m; i++) {
        int t, x;
        cin >> t >> x;
        //   cout << i << " : ";
        if (t == 1) {
            add(x);
            cursz++;
        } else if (t == -1) {
            remove(x);
            cursz--;
        } else if (t == 0) {
            int kth = get_kth(root, cursz - x + 1);
            cout << kth << "\n";
        }
        //  cout << "\n-------------\n";
    }
    return 0;
}
