#include <iostream>

using namespace std;

#define MAXN 50001

struct {

                int l, r, lc, rc, f, id;

} nod[MAXN*3];

unsigned int st[MAXN], l;

void creat(int t, int l, int r) {

                nod[t].l = l, nod[t].r = r, nod[t].f = 1;

                nod[t].id = (l+r) >> 1;

                nod[t].lc = nod[t].id - l, nod[t].rc = r - nod[t].id;

                if(nod[t].id != l) creat(t*2, l, nod[t].id-1);

                if(nod[t].id != r) creat(t*2+1, nod[t].id+1, r);

}

int getL(int t) {

                if(nod[t].id - nod[t].l == nod[t].lc) return nod[t].lc + (nod[t].f ? nod[t].rc + nod[t].f : 0);

                return getL(t*2);

}

int getR(int t) {

                if(nod[t].r - nod[t].id == nod[t].rc) return nod[t].rc + (nod[t].f ? nod[t].lc + nod[t].f : 0);

                return getR(t*2+1);

}

void RandD(int t, int num, int f) {

                if(num == nod[t].id) nod[t].f = f;

                else if(num < nod[t].id) {

                                RandD(t*2, num, f);

                                if(!(num < nod[t*2].id && (!nod[t*2].f || nod[t*2].r - nod[t*2].id > nod[t*2].rc))) nod[t].lc = getR(t*2);

                } else {

                                RandD(t*2+1, num, f);

                                if(!(num > nod[t*2+1].id && (!nod[t*2+1].f || nod[t*2+1].id - nod[t*2+1].l > nod[t*2+1].lc))) nod[t].rc = getL(t*2+1);

                }

}

int query(int t, int num) {

                if(num == nod[t].id) return nod[t].f ? nod[t].f + nod[t].lc + nod[t].rc : 0;

                else if(num < nod[t].id) {

                                if(num >= nod[t].id - nod[t].lc) return nod[t].lc + (nod[t].f ? nod[t].f + nod[t].rc : 0);

                                else return query(t*2, num);

                } else {

                                if(num <= nod[t].id + nod[t].rc) return nod[t].rc + (nod[t].f ? nod[t].f + nod[t].lc : 0);

                                else return query(t*2+1, num);

                }

}

int main() {

                int n, m, t;

                char s[2];

                while(scanf("%d%d", &n, &m) != EOF) {

                                l = 0;

                                creat(1, 1, n);

                                while(m--) {

                                                scanf("%s", s);

                                                switch(s[0]) {

                                                                case 'D':

                                                                                scanf("%d", &t);

                                                                                st[l++] = t;

                                                                                RandD(1, t, 0);

                                                                                break;

                                                                case 'R':

                                                                                RandD(1, st[--l], 1);

                                                                                break;

                                                                default:

                                                                                scanf("%d", &t);

                                                                                printf("%d\n", query(1, t));

                                                }

                                }

                }

                return 0;

}

