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
    string s;
    cin >> s;
    int n = len(s);
    vector <int> pref(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pref[i - 1];
        while (j > 0 && s[j] != s[i]) {
            j = pref[j - 1];
        }
        if (s[j] == s[i]) {
            j++;
        }
        pref[i] = j;
    }
    for (int i = 0; i < n; i++) {
        cout << pref[i] << ' ';
    }
    return 0;
}
