
#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) x.begin(), x.end()
#define len(x) int(x.size())
 
typedef long long ll;
 
void gen(int l, int r, ll sum, int C, vector <int> &a, vector <ll> &dest) {
    if (l == r) {
        if (sum <= C) {
            dest.push_back(sum);
        }
    } else {
        gen(l + 1, r, sum + a[l], C, a, dest);
        gen(l + 1, r, sum, C, a, dest);
    }
}
 
int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, C;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> C;
    int m = n / 2;
    vector <ll> left;
    vector <ll> right;
    gen(0, m, 0, C, a, left);
    gen(m, n, 0, C, a, right);
    sort(all(left));
    sort(all(right));
    int ans = 0;
    for (int i = 0; i < len(left); i++) {
        if (left[i] <= C) {
//            ans++;
            int pos = upper_bound(all(right), C - left[i]) - right.begin();
            ans += pos;
        }
    }
    cout << ans;
    return 0;
} 
