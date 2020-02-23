#include <bits/stdc++.h>

using namespace std;

int n;
double a;

bool check(double m) {
    vector <double> v(n);
    v[0] = a;
    v[1] = m;
    for (int i = 2; i < n; i++) {
        v[i] = (2.0 * v[i - 1] - v[i - 2] + 2.0);
    }
    for (int i = 0; i < n; i++) {
        if (v[i] <= 0)
            return false;
    }
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> a;
    double l = 0, r = 1e9;
    for (int i = 0; i < 50; i++) {
        double m = (l + r) / 2;
        if (check(m))
            r = m;
        else
            l = m;
    }
    vector <double> v(n);
    v[0] = a;
    v[1] = l;
    for (int i = 2; i < n; i++)
    	v[i] = 2.0 * v[i - 1] - v[i - 2] + 2.0;
    cout << fixed;
    cout.precision(2);
    cout << v[n - 1];
    return 0;
}
