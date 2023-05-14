#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int N = 2000 ;
int Q = 2000 ;
int M = 2000 ;

int main() {
	registerValidation();
	int n = inf.readInt(1, N) ; inf.readSpace() ;
	int q = inf.readInt(0, Q) ; inf.readEoln() ;
	
	multiset<string> st ;
	string rgx = "[a-z]{1," + to_string(M) + "}" ;
	string s ;
	int m = - 1 ;
	for(int i=0; i<n; ++i) {
		s = inf.readString(rgx) ;
		st.insert(s) ;
		if (m == -1)
			m = s.size() ;
		else 
			ensuref(m == s.size(), "%d: string not same size!\n", i+1) ;
	}

	int k ;
	for(int i=0; i<q; ++i) {
		k = inf.readInt(1, 2) ; inf.readSpace() ;
		s = inf.readString(rgx) ; 
		ensuref(m == s.size(), "op %d: string not same size!\n", i+1) ;
		if (k == 1) {
			st.insert(s) ;
		} else {
			ensuref(st.count(s) > 0, "op %d: string is not in S!\n", i+1) ;
			st.erase(st.lower_bound(s)) ;
		}
	}
	inf.readEof() ;
}
