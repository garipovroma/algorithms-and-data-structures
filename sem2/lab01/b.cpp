#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

struct Node {
    Node *l, *r, *p;
    int x;
    Node() {
        l = r = nullptr;
    }
    Node(int a) {
        x = a;
        l = r = p = nullptr;
    }
    Node(int a, Node* parent) {
        x = a;
        l = r = nullptr;
        p = parent;
    }
};

const int N = 1e5 + 228;
Node Nodes[N];
int cur_pos = 0;

Node *nwNode(int x) {
    Nodes[cur_pos++] = Node(x);
    return &Nodes[cur_pos - 1];
}

void set_parent(Node *&v, Node *p) {
    if (v != nullptr) {
        v->p = p;
    }
}

void keep_parent(Node *&v) {
    set_parent(v->l, v);
    set_parent(v->r, v);
}

void rotate(Node *&v, Node *&p) {
    Node *g = p->p;
    if (g != nullptr) {
        if (g->l == p) {
            g->l = v;
        } else {
            g->r = v;
        }
    }
    if (p->l == v) {
        p->l = v->r;
        v->r = p;
    } else {
        p->r = v->l;
        v->l = p;
    }
    keep_parent(v);
    keep_parent(p);
    v->p = g;
}

Node* splay(Node *&v) {
    if (v->p == nullptr) {
        return v;
    }
    Node *p = v->p;
    Node *g = p->p;
    if (g == nullptr) {    //    zig
        rotate(v, p);
        return v;
    } else {
        bool f = (p->l == v) == (g->l== p);
        if (f) {   //   zig-zig
            rotate(p, g);
            rotate(v, p);
        } else {   //   zig-zag
            rotate(v, p);
            rotate(v, g);
        }
        return splay(v);
    }
}

void dfs(Node *v) {
    if (v == nullptr) {
        return;
    }
    cout << v->x << ' ';
    dfs(v->l);
    dfs(v->r);
}

Node *root = nullptr;

Node *find(Node *v, int x) {
    if (v == nullptr) {
        return nullptr;
    }
    if (v->x == x) {
        return splay(v);
    } else if (v->x < x && v->r != nullptr) {
        return find(v->r, x);
    } else if (v->x > x && v->l != nullptr) {
        return find(v->l, x);
    }
    return splay(v);
}

bool find(int x) {
    root = find(root, x);
    return (root != nullptr && root->x == x);
}

pair <Node*, Node*> split(Node *&v, int k) {
    if (v == nullptr) {
        return {nullptr, nullptr};
    }
    Node *root = find(v, k);
    if (root->x == k) {
        set_parent(root->l, nullptr);
        set_parent(root->r, nullptr);
        return {root->l, root->r};
    } else if (root->x < k) {
        Node *cur = root->r;
        set_parent(cur, nullptr);
        root->r = nullptr;
        return {root, cur};
    } else {
        Node *cur = root->l;
        set_parent(cur, nullptr);
        root->l = nullptr;
        return {cur, root};
    }
}

void add(int x) {
    if (root == nullptr) {
        root = nwNode(x);
        return;
    }
    pair <Node*, Node*> t = split(root, x);
    root = nwNode(x);
    root->l = t.first;
    root->r = t.second;
    keep_parent(root);
}

Node *merge(Node *&vl, Node *&vr) {
    if (vl == nullptr) {
        return vr;
    }
    if (vr == nullptr) {
        return vl;
    }
    vr = find(vr, vl->x);
    vr->l = vl;
    keep_parent(vr);
    return vr;
}

void remove(int x) {
    root = find(root, x);
    set_parent(root->l, nullptr);
    set_parent(root->r, nullptr);
    root = merge(root->l, root->r);
}


int next(int x) {
    root = find(root, x);
    if (root == nullptr) {
        return 1e9 + 1;
    }
    if (root->x > x) {
        return root->x;
    }
    if (root->r == nullptr) {
        return 1e9 + 1;
    }
    Node *cur = root->r;
    int val = (root->x > x ? root->x : (int)1e9 + 1);
    Node *was;
    while (cur != nullptr) {
        val = min(cur->x, val);
        was = cur;
        cur = cur->l;
    }
    root = splay(was);
    return val;
}

int prev(int x) {
    root = find(root, x);
    if (root == nullptr) {
        return 1e9 + 1;
    }
    if (root->x < x) {
        return root->x;
    }
    if (root->l == nullptr) {
        return 1e9 + 1;
    }
    Node *cur = root->l;
    int val = (root->x < x ? root->x : (int)-1e9 - 1);
    Node *was;
    while (cur != nullptr) {
        val = max(val, cur->x);
        was = cur;
        cur = cur->r;
    }
    root = splay(was);
    return val;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   //   HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    while (cin >> s) {
        if (s == "insert") {
            int x;
            cin >> x;
            if (find(x)) {
                continue;
            }
            add(x);
        } else if (s == "exists") {
            int x;
            cin >> x;
            if (find(x)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (s == "next") {
            int x;
            cin >> x;
            int y = next(x);
            if (y == 1e9 + 1) {
                cout << "none\n";
            } else {
                cout << y << "\n";
            }
        } else if (s == "prev") {
            int x;
            cin >> x;
            int y = prev(x);
            if (y == 1e9 + 1) {
                cout << "none\n";
            } else {
                cout << y << "\n";
            }
        } else if (s == "delete") {
            int x;
            cin >> x;
            if (!find(x)) {
                continue;
            }
            remove(x);
        }
    }
    return 0;
}
