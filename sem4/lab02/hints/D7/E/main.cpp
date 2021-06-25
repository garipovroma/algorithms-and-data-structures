#include <bits/stdc++.h>

using namespace std;
                                 
int get_p(int x, vector <int> &p){
	if (((x + 1) % ((x + 1) - p[x])) == 0)
		return (x + 1) / ((x + 1) - p[x]);	 	
	else
		return 1;
}

int main(){
 	#ifdef HOME
 	freopen("input.txt", "rt", stdin);
 	#else
 	freopen("periodic.in", "rt", stdin);
 	freopen("periodic.out", "wt", stdout);
 	#endif //HOME
 	string s;
 	cin >> s;
 	int n = s.length();
 	vector <int> p(n, 0);
 	for (int i = 1; i < n; i++){
 	 	int j = p[i - 1];
 	 	while(j >0 && s[i] != s[j])
 	 		j = p[j - 1];
 	 	if (s[j] == s[i]) j++;
 	 	p[i] = j;
 	}                       /*
 	for (int i = 0; i < n; i++)
 		cout << p[i] << ' ';*/
 	for (int i = 0; i < n; i++){
 		cout << get_p(i, p) << ' ';
 	}
 	return 0;
}