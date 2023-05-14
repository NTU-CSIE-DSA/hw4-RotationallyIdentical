#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int N = 1000000 ;
int Q = 0 ;
int M = 1000000 ;

int main() {
	registerValidation();
	int n = inf.readInt(1, N) ; inf.readSpace() ;
	int q = inf.readInt(0, Q) ; inf.readEoln() ;
	
	string rgx = "[a-z]{1," + to_string(M) + "}" ;
	string s ;
	for(int i=0; i<n; ++i) {
		s = inf.readString(rgx) ;
	}

	for(int i=0; i<q; ++i) {
		int k = inf.readInt(1, 2) ; inf.readSpace() ;
		s = inf.readString(rgx) ;
	}
	inf.readEof() ;
}
