#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int N = 1000000 ;
int Q = 1000000 ;
int M = 1000000 ;
long long nqm = 1000000 ;

int main() {
	registerValidation();
	int n = inf.readInt(1, N) ; inf.readSpace() ;
	int q = inf.readInt(0, Q) ; inf.readEoln() ;
	
	unordered_multiset<string> st ;
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
			auto it = st.find(s) ;
			ensuref(it != st.end(), "op %d: string is not in S!\n", i+1) ;
			st.erase(it) ;
		}
	}

	ensuref(1LL* (n+q)*m <= nqm, "(n+q)m too large!\n") ;
	inf.readEof() ;
}
