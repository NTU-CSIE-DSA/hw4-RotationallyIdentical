/*

generate monotonic hash values

*/

#include "testlib.h"
#include <bits/stdc++.h>
using namespace std ;

vector<string> pool ;
int idx, rev ;
string cur_str ;
int MX = 1000000 ;

void dfs(int cur, int dep, int mn) {
	if (pool.size() >= MX)
		return ;
	if (cur == dep) {
		pool.emplace_back(cur_str) ;
		return ;	
	}
	if (rev) {
		for(int i=mn; i<26; ++i) {
			cur_str += 'a' + i ;
			dfs(cur+1, dep, i) ;
			cur_str.pop_back() ;
		}
	} else {
		for(int i=mn; i>=0; --i) {
			cur_str += 'a' + i ;
			dfs(cur+1, dep, i) ;
			cur_str.pop_back() ;
		}
	}

}

string get_str() {
	string ret = pool[idx++] ;
	if (idx == pool.size())
		idx = 0 ;
	return ret ;
}

int main(int argc, char *argv[]) {
	ios::sync_with_stdio(false) ;
	cin.tie(0) ;

	registerGen(argc, argv, 1) ;
	int n = atoi(argv[1]) ; // initial size
	int q = atoi(argv[2]) ; // operation
	int m = atoi(argv[3]) ; // length
	int r = -atoi(argv[4]) ; // tend to insert (+) / remove (-)
	rev = atoi(argv[5]) ; // reverse

	if (rev)
		dfs(0, m, 0) ;
	else 
		dfs(0, m, 25) ;

	string s ;
	vector<string> v ;

	cout << n << ' ' << q << '\n' ; 
	for(int i=0; i<n; ++i) {
		s = get_str() ;	
		cout << s << '\n' ;
		v.emplace_back(s) ;
	}

	for(int i=0; i<q; ++i) {
		int k = rnd.wnext(2, r) + 1;
		if (k == 1 || v.size() == 0) {
			s = get_str() ;
			cout << "1 " << s << '\n' ;
			v.emplace_back(s) ;
		} else {
			int idx = rnd.next(v.size()) ;
			s = v[idx] ;
			v[idx] = v.back() ;
			v.pop_back() ;
			cout << "2 " << s << '\n' ;
		}
	}
}