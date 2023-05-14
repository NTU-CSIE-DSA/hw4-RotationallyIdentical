/*

1. rolling hash for M rotations 
2. sum the reciprocals of the M values as blueprint

WA on short, fully random inputs. 
O(NlogNlogN)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 1000010
#define Q 0xCC12
// #define P 136352001050389LL  // a 47 bit prime generated via PyCryptodome
#define P 1163867213LL // a 31 bit prime generated via PyCryptodome 
// should ensure P * P <= MAX_LL

long long Qpow[M] ;
long long hs[M] ;

long long POW(long long x, long long k) {
    long long ret = 1 ;
    while(k) {
        if (k & 1) ret = (ret * x) % P ;
        x = (x * x) % P ; 
        k >>= 1 ;
    }
    return ret ;
}

long long hash(char s[]) {
    int n = strlen(s) ;

    // Calculate the hashes of s[0, n-1], s[1, (n)%n], ..., s[n, (2n-1)%n]
    hs[0] = 0 ;
    for(int i=0; i<n; ++i)
        hs[0] = (hs[0] * Q + s[i]) % P ;
    for(int i=1; i<n; ++i) 
        hs[i] = ((hs[i-1] - s[i-1] * Qpow[n-1] % P + P) % P * Q + s[i-1]) % P ;

    // Calculate the hash of the n hashes as the blueprint
    long long ret = 0 ;
    for(int i=0; i<n; ++i) {
        ret = (ret + POW(hs[i], P-2)) % P ;
    }    
    return ret ;
} 

void init() {
    Qpow[0] = 1 ;
    for (int i=1; i<M; ++i)
        Qpow[i] = Qpow[i-1] * Q % P ;
}

typedef struct nodeT {
    long long value ;
    int count ;
    struct nodeT *lch, *rch ;
} node ;
node *root ;

void node_insert(long long x, node *p) {
    if (p -> value == 0 || p -> value == x) {
        p -> value = x ;
        p -> count ++ ;
        return ;
    }
    if (x > p -> value) {
        if (p -> rch == NULL)
            p -> rch = (node *)calloc(1, sizeof(node)) ;
        node_insert(x, p -> rch) ;
    } else {
        if (p -> lch == NULL)
            p -> lch = (node *)calloc(1, sizeof(node)) ;
        node_insert(x, p -> lch) ;
    }
}

void insert(long long x) {
    if (root == NULL)
        root = (node *)calloc(1, sizeof(node)) ;
    node_insert(x, root) ;
}

node *node_max(node *p) {
    if (p -> rch == NULL)
        return p ;
    return node_max(p -> rch) ; 
}

node* node_delete(long long x, node *p) {
    if (p == NULL)
        return NULL ;
    if (x > p -> value) {
        p -> rch = node_delete(x, p -> rch) ;
        return p ; 
    }
    if (x < p -> value) {
        p -> lch = node_delete(x, p -> lch) ;
        return p ;
    }

    node *lch = p -> lch ;
    node *rch = p -> rch ;
    if (lch == NULL && rch == NULL) {
        free(p) ;
        return NULL ;
    } else if (lch == NULL) {
        free(p) ;
        return rch ;
    } else if (rch == NULL) {
        free(p) ;
        return lch ;
    } else {
        node *tmp = node_max(p -> lch) ;
        p -> value = tmp -> value ;
        p -> count = tmp -> count ;
        p -> lch = node_delete(tmp -> value, p -> lch) ;
        return p ;
    }
}

node* node_subtract(long long x, node *p) {
    if (p -> value == x) {
        if ((--(p -> count)) == 0) 
            return node_delete(x, p) ;
        return p ;
    }
    if (x > p -> value)
        p -> rch = node_subtract(x, p -> rch) ;
    else 
        p -> lch = node_subtract(x, p -> lch) ;
    return p ;
}

void subtract(long long x) {
    root = node_subtract(x, root) ;
}

int node_count(long long x, node *p) {
    if (p == NULL)
        return 0 ;
    if (p -> value == x) 
        return p -> count ;
    if (x > p -> value)
        return node_count(x, p -> rch) ;
    else
        return node_count(x, p -> lch) ;
}

int count(long long x) {
    return node_count(x, root) ;
}

char s[M] ;

int main() {
    init() ;

    int n, q ;
    long long ans = 0 ;

    scanf("%d%d", &n, &q) ;
    for(int i=0; i<n; ++i) {
        scanf("%s", s) ;
        long long hs = hash(s) ;
        ans += count(hs) ;
        insert(hs) ;
        // printf("[debug] %d: %s %lld\n", i+1, s, hs) ;
    }

    printf("%lld\n", ans) ;
    int k ;
    for(int i=0; i<q; ++i) {
        scanf("%d %s", &k, s) ;
        long long hs = hash(s) ;
        // printf("[debug] %d: %d %s %lld\n", i+1, k, s, hs) ;
        if (k == 1) {
            ans += count(hs) ;
            insert(hs) ;
        } else {
            subtract(hs) ;
            ans -= count(hs) ;
        }
        printf("%lld\n", ans) ;
    }
}