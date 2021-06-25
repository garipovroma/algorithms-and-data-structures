#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string a, b;
    cin >> a >> b;
    string s = a + "#" + b;
    int m = len(s);
    vector <int> pref(m, 0);
    for (int i = 1; i < m; i++) {
        int j = pref[i - 1];
        while (j > 0 && s[j] != s[i]) {
            j = pref[j - 1];
        }
        if (s[j] == s[i]) {
            j++;
        }
        pref[i] = j;
    }
    vector <int> ind;
    for (int i = len(a); i < m; i++) {
        if (pref[i] == len(a)) {
            ind.push_back(i - 2 * len(a) + 1);
        }
    }
    cout << len(ind) << "\n";
    for (int i: ind) {
        cout << i << ' ';
    }
    return 0;
}
