#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

int myrand() {
    return rand();
}

int ss = 0;

const int N = 3e7 + 10;

int v[N];

int partition(int l, int r) {
    int i = l, j = r;
    int val = v[(l + r) / 2];
    // int m = (l + r) / 2;
    // int val = a[m];
    while (i <= j) {
        while (v[j] > val) {
            j--;
        }
        while (v[i] < val) {
            i++;
        }
        if (i >= j) {
            break;
        }
        swap(v[i], v[j]);
        i++;
        j--;
    }
    return j;
}

int qsort(int l, int r, int k) {
    /* ss++;
    if (ss == 50) return -1;*/
    //  cout << l << ' ' << r << ' ' << k << endl;
    //  cout << l << ' ' << r << ' ';
    if (r - l < 10) {
        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                if (v[i] > v[j])
                    swap(v[i], v[j]);
            }
        }
        return v[k];
    }
    int x = partition(l, r);
    //  cout << x << endl;
    if (x == k)
        return v[x];
    if (x > k)
        return qsort(l, x, k);
    else
        return qsort(x + 1, r, k);
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //  srand(time(nullptr));
    /*int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];
    int k;
    cin >> k;
    cout << qsort(0, n - 1, k - 1);*/

    int n, k, a, b, c;

    cin >> n >> k >> a >> b >> c;
    cin >> v[0] >> v[1];
    for (int i = 2; i < n; i++)
        v[i] = v[i - 2] * a + v[i - 1] * b + c;
    /* for (int i = 0; i < n; i++)
        cout << v[i] << ' ';
    cout << endl;  */
    cout << qsort(0, n - 1, k - 1);
    return 0;
}
