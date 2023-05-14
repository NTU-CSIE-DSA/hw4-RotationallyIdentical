#include <stdio.h>
#include <string.h>

#define NQ 110
#define M 60
int valid[NQ] ;
char s[NQ][M] ;

int check(int x, int y) {
    int m = strlen(s[x]) ;
    for(int i=0; i<m; ++i) {
        int flag = 1 ;
        for(int j=0; j<m; ++j)
            if (s[x][j] != s[y][(j+i)%m])
                flag = 0 ;
        if (flag)
            return 1 ;
    }
    return 0 ;
}

int count() {
    int ret = 0 ;
    for (int i=0; i<NQ; ++i) {
        if (valid[i] == 0)
            continue ;
        for (int j=i+1; j<NQ; ++j) {
            if (valid[j] == 0)
                continue ;
            ret += check(i, j) ;
        }
    }
    return ret ;
}


int main() {
    int n, q, k ;
    scanf("%d%d", &n, &q) ;
    for(int i=0; i<n; ++i) {
        scanf("%s", s[i]) ;
        valid[i] = 1 ;
    }
    
    printf("%d\n", count()) ;
    char t[M] ;
    for(int i=0; i<q; ++i) {
        scanf("%d%s", &k, t) ;
        if (k == 1) {
            for(int j=0; j<NQ; ++j) {
                if (valid[j] == 0) {
                    strcpy(s[j], t) ;
                    valid[j] = 1 ;
                    break ;
                }
            }
        } else {
            for(int j=0; j<NQ; ++j) {
                if (valid[j] && strcmp(t, s[j]) == 0) {
                    valid[j] = 0 ;
                    break ;
                }
            }
        }
        printf("%d\n", count()) ;
    }

}