#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std ;

string booth(string s) {
    int n = s.size() ;
    int t = 0 ;     // start position of the current smallest string
    int k = -1 ;    // failure number
    s += s ;
    vector<int> f(2*n, -1) ;

    for(int i=1; i<2*n; ++i) {
        while(k != -1 && s[t + (k+1)] != s[i]) {
            if (s[t + (k+1)] > s[i]) // the new string s[i-(k+1), i] is smaller
                t = i - (k+1) ;
            k = f[k] ;
        }
        if (s[t + (k+1)] == s[i])
           ++k ;
        else if (s[t] > s[i])
            t = i ;
        f[i - t] = k ;
    }

    string ret ;
    for(int i=0; i<n; ++i)
        ret += s[t + i] ;
    return ret ;
}

int main() {
    ios::sync_with_stdio(false) ;
    cin.tie(0) ; cout.tie(0) ;

    int n, q, ans = 0 ;
    string s ;
    unordered_map<string, int> mp ;

    cin >> n >> q ;
    for(int i=0 ;i<n; ++i) {
        cin >> s ;
        s = booth(s) ;
        ans += mp[s] ;
        mp[s] ++ ;
    }
    cout << ans << '\n' ;

    int k ;
    for(int i=0; i<q; ++i) {
        cin >> k >> s ;
        s = booth(s) ;
        if (k == 1) {
            ans += mp[s] ;
            mp[s] ++ ;
        } else {
            mp[s] -- ;
            ans -= mp[s] ;
        }
        cout << ans << '\n' ;
    }
}