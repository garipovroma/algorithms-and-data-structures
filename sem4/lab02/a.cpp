#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5;
const int ALPHABET = 26;

struct Node {
    Node *go[ALPHABET];
    bool term;
    int id;
    Node() {
        term = false;
        for (int i = 0; i < ALPHABET; i++) {
            go[i] = nullptr;
        }
    }
};

Node nodes[N];
int pointer = 0;

Node* newNode() {
    nodes[pointer].id = pointer + 1;
    return &nodes[pointer++];
}

Node *root = newNode();

void add_string(string &s) {
    Node *cur = root;
    for (int i = 0; i < len(s); i++) {
        int ch = s[i] - 'a';
        if (cur->go[ch] == nullptr) {
            cur->go[ch] = newNode();
        }
        cur = cur->go[ch];
    }
    cur->term = true;
}

void dfs(Node *v) {
    for (int i = 0; i < ALPHABET; i++) {
        if (v->go[i] != nullptr) {
            Node *u = v->go[i];
            cout << v->id << ' ' << u->id << ' ' << char(i + 'a') << "\n";
            dfs(u);
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
    string s;
    cin >> s;
    int n = len(s);
    for (int i = 0; i < n; i++) {
        string cur = s.substr(i, n - i);
        add_string(cur);
    }
    cout << pointer << ' ' << pointer - 1 << "\n";
    dfs(root);
    return 0;
} 
