#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

vector<int> calc_pref(string &s) {
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
    return pref;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    string s;
    cin >> s;
    int n = len(s);
    vector <int> pref = calc_pref(s);
    int ans = ((n % (n - pref[n - 1]) == 0) ? (n - pref[n - 1]) : n);
    cout << ans;
    return 0;
} 
