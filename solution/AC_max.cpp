#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 2010
#define Q 0xCC12
#define P 136352001050389LL  // a 47 bit prime generated via PyCryptodome

long long Qpow[M] ;

long long hash(char s[]) {
    int n = strlen(s) ;

    // Calculate the hashes of s[0, n-1], s[1, (n)%n], ..., s[n, (2n-1)%n]
    long long hs[M] = {} ;
    for(int i=0; i<n; ++i)
        hs[0] = (hs[0] * Q + s[i]) % P ;
    for(int i=1; i<n; ++i) 
        hs[i] = ((hs[i-1] - s[i-1] * Qpow[n-1] % P + P) % P * Q + s[i-1]) % P ;

    // Calculate the hash of the n hashes as the blueprint
    long long ret = 0 ;
    for(int i=0; i<n; ++i) {
        if (ret < hs[i])
            ret = hs[i] ; 
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

int main() {
    init() ;

    int n, q, ans = 0 ;
    char s[M] ;

    scanf("%d%d", &n, &q) ;
    for(int i=0; i<n; ++i) {
        scanf("%s", s) ;
        long long hs = hash(s) ;
        ans += count(hs) ;
        insert(hs) ;
        // printf("[debug] %d: %s %lld\n", i+1, s, hs) ;
    }

    printf("%d\n", ans) ;
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
        printf("%d\n", ans) ;
    }
}