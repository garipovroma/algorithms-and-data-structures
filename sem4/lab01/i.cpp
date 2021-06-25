#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

struct Node{
    int go[26], sl, ssl, p, pch;
    int term;
    Node(){
        term = -1;
        for (int i = 0; i < 26; i++){
            go[i] = -1;
        }
        sl = -1;
        ssl = -1;
        p = -1;
        pch = -1;
    }
};

int get_go(int v, int c);
int get_sl(int v);
int get_ssl(int v);

vector <Node> trie;
vector <int> vert;
int root = 0;

void add(string &s, int id){
    int cur = 0;
    for (int i = 0; i < len(s); i++){
        if (trie[cur].go[s[i] - 'a'] == -1){
            trie[cur].go[s[i] - 'a'] = len(trie);
            trie.push_back(Node());
        }
        int nw = trie[cur].go[s[i] - 'a'];
        if (trie[nw].p == -1){
            trie[nw].p = cur;
            trie[nw].pch = s[i] - 'a';
        }
        cur = nw;
    }
    trie[cur].term = cur;
    vert[id] = cur;
}

int get_sl(int v){
    if (trie[v].sl != -1) return trie[v].sl;
    if (trie[v].p == -1){
        trie[v].sl = -1;
        return trie[v].sl;
    }
    trie[v].sl = get_go(get_sl(trie[v].p), trie[v].pch);
    return trie[v].sl;
}

int get_ssl(int v){
    if (trie[v].ssl != -1) return trie[v].ssl;
    if (trie[v].p == -1){
        trie[v].ssl = -1;
        return -1;
    }
    if (trie[v].term != -1){
        trie[v].ssl = v;
        return trie[v].ssl;
    }
    else{
        trie[v].ssl = get_ssl(trie[v].sl);
        return trie[v].ssl;
    }
}

int get_go(int v, int c){
    if (v == -1) return 0;
    if (trie[v].go[c] != -1) return trie[v].go[c];
    trie[v].go[c] = get_go(get_sl(v), c);
    return trie[v].go[c];
}

vector <string> a;
string t;

int main(){
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif    // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    trie.push_back(Node());
    int n;
    cin >> t >> n;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vert.resize(n);
    for (int i = 0; i < n; i++){
        add(a[i], i);
    }
    for (int i = 0; i < len(trie); i++){
        trie[i].sl = get_sl(i);
        for (int c = 0; c < 26; c++)
            trie[i].go[c] = get_go(i, c);
    }
    for (int i = 0; i < len(trie); i++)
        trie[i].ssl = get_ssl(i);
    vector <bool> ans(len(trie), false);
    int cur = 0;
    for (int i = 0; i < len(t); i++){
        int c = t[i] - 'a';
        cur = trie[cur].go[c];
        int x = cur;
        while(x > 0){
            x = trie[x].ssl;
            if (x == -1) break;
            if (ans[trie[x].term])
                break;
            else
                ans[trie[x].term] = true;
            x = trie[x].sl;
        }
    }
    for (int i = 0; i < n; i++)
        if (ans[vert[i]])
            cout << "Yes\n";
        else
            cout << "No\n";
    return 0;
}
 
