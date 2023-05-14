#include "testlib.h"
#include <bits/stdc++.h>
using namespace std ;

int main(int argc, char *argv[]) {
	ios::sync_with_stdio(false) ;
	cin.tie(0) ;

	registerGen(argc, argv, 1) ;
	int n = atoi(argv[1]) ; // initial size
	int q = atoi(argv[2]) ; // operation
	int m = atoi(argv[3]) ; // length
	int r = -atoi(argv[4]) ; // tend to insert (+) / remove (-)
	int w = -atoi(argv[5]) ; // tend to select lower characters in set
	string ch = argv[6] ;	// character set

	string s ;
	vector<string> v ;

	cout << n << ' ' << q << '\n' ; 
	for(int i=0; i<n; ++i) {
		s.clear() ;
		for(int j=0; j<m; ++j) {
			int p = rnd.wnext(ch.size(), w) ;
			s += ch[p] ;
		}
		cout << s << '\n' ;
		v.emplace_back(s) ;
	}

	for(int i=0; i<q; ++i) {
		int k = rnd.wnext(2, r) + 1;
		if (k == 1 || v.size() == 0) {
			s.clear() ;
			for(int j=0; j<m; ++j) {
				int p = rnd.wnext(ch.size(), w) ;
				s += ch[p] ;
			}
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