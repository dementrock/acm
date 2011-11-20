/* Edge Constructor */

struct Edge
{
	int v;
	double w;
	Edge *next;
} *edge[MAXM+1],mempool[MAXM+1];

int memnum = 0;

void add(int u, int v, double w)
{
	Edge *e=&mempool[++memnum];
	e->v=v;
	e->w=w;
	e->next=edge[u];
	edge[u]=e;
}

/* SPFA */

int spfa()
{
    int start = 0, end = n + 1;
    for (int i = start + 1; i <= end; ++i) {
        dis[i] = INFTY;
    }
    vis[start] = 1;
    que[0] = start;
    cnt_vis[start] = 1;
    int tail = -1, head = 0, cnt_elements = 1;
    while (cnt_elements) {
        tail = (tail + 1) % (end + 1);
        --cnt_elements;
        int now = que[tail];
        if (cnt_vis[now] > 2 * end) {
            return 1;
        }
        for (Edge *e = edge[now]; e != NULL; e = e -> next) {
            int new_len = e -> w + dis[now];
            int to = e -> v;
            if (new_len < dis[to]) {
                dis[to] = new_len;
                if (!vis[to]) {
                    ++cnt_elements;
                    head = (head + 1) % (end + 1);
                    vis[to] = 1;
                    que[head] = to;
                    ++cnt_vis[to];
                    if (cnt_vis[to] > 2 * end) {
                        return 1;
                    }
                }
            }
        }
        vis[now] = 0;
    }
    return 0;
}

/* SAP */
struct Edge
{
	int v;
	int w;
	Edge *next, *reverse;
} *edge[MAXM],mempool[MAXM];

int memnum;

int v[MAXN][MAXN], layer[MAXN], minf = INFTY, counter[MAXN], found = 0, ans = 0, start, end;

void add(int u, int v, int w)
{
    Edge *e1 = &mempool[++memnum], *e2 = &mempool[++memnum];
    e1 -> v = v, e2 -> v = u;
    e1 -> w = w, e2 -> w = 0;
    e1 -> next = edge[u], e2 -> next = edge[v];
    e1 -> reverse = e2, e2 -> reverse = e1;
    edge[u] = e1, edge[v] = e2;
}

void aug(int now) {
    int i, cache_minf = minf, minl = end;
    if (now == end) {
        found = 1;
        ans += minf;
        return;
    }
    Edge *e;
    for (e = edge[now]; e != NULL; e = e -> next) {
        if (e -> w > 0) {
            if (layer[now] == layer[e -> v] + 1) {
                minf = min(minf, e -> w);
                aug(e -> v);
                if (layer[start] > end) {
                    return;
                }
                if (found) {
                    break;
                }
                minf = cache_minf;
            }
            if (layer[e -> v] < minl) {
                minl = layer[e -> v];
            }
        }
    }
    if (!found) {
        if (--counter[layer[now]] == 0) {
            layer[start] = end + 1;
        }
        ++counter[layer[now] = minl + 1];
    } else {
        e -> w -= minf;
        e -> reverse -> w += minf;
    }
}

void sap() {
    memset(layer, 0, sizeof(layer));
    memset(counter, 0, sizeof(counter));
    counter[0] = end + 1;
    ans = 0;
    while (layer[start] <= end) {
        minf = INFTY;
        found = 0;
        aug(start);
    }
}

/* Bipartet Hungarian Algorithm */

int can (int t) {
    int i;
    for (i = 1; i <= n + p; ++i) {
        if (!used[i] && v[t][i]) {
            used[i] = 1;
            if (!linked[i] || can(linked[i])) {
                linked[i] = t;
                return 1;
            }
        }
    }
    return 0;
}

void hungarian() {
    ans = 0;
    for (int i = 1; i <= p; ++i) {
        memset(used, 0, sizeof(used));
        ans += can(i);
    }
}

/* Kruskal */

struct edge{
    int x, y;
    int l;
} e[MAXM];

int cnt_e = 0, father[MAXN], ans = 0;

void add_edge(int x, int y, int l){
    e[++cnt_e].x = x;
    e[cnt_e].y = y;
    e[cnt_e].l = l;
}

int getfather(int x){
    if (father[x] == x) {
        return x;
    }
    return father[x] = getfather(father[x]);
}

void merge(int x, int y, int l){
    int a = getfather(x), b = getfather(y);
    if (a != b) {
        ans += l;
        father[a] = b;
    }
}

int cmp(const void *x, const void *y){
    edge *a = (edge *) x;
    edge *b = (edge *) y;
    return a -> l - b -> l;
}

void kruskal(){
    qsort(e + 1, cnt_e, sizeof(e[0]), cmp);
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
    }
    for (int i = 1; i <= cnt_e; ++i){
        merge(e[i].x, e[i].y, e[i].l);
    }
}

/* BigNum */
#include<iostream> 
#include<string> 
#include<iomanip> 
#include<algorithm> 
using namespace std; 

#define MAXN 9999
#define MAXSIZE 10
#define DLEN 4

class BigNum
{ 
private: 
	int a[500];    //可以控制大数的位数 
	int len;       //大数长度
public: 
	BigNum(){ len = 1;memset(a,0,sizeof(a)); }   //构造函数
	BigNum(const int);       //将一个int类型的变量转化为大数
	BigNum(const char*);     //将一个字符串类型的变量转化为大数
	BigNum(const BigNum &);  //拷贝构造函数
	BigNum &operator=(const BigNum &);   //重载赋值运算符，大数之间进行赋值运算

	friend istream& operator>>(istream&,  BigNum&);   //重载输入运算符
	friend ostream& operator<<(ostream&,  BigNum&);   //重载输出运算符

	BigNum operator+(const BigNum &) const;   //重载加法运算符，两个大数之间的相加运算 
	BigNum operator-(const BigNum &) const;   //重载减法运算符，两个大数之间的相减运算 
	BigNum operator*(const BigNum &) const;   //重载乘法运算符，两个大数之间的相乘运算 
	BigNum operator/(const int   &) const;    //重载除法运算符，大数对一个整数进行相除运算

	BigNum operator^(const int  &) const;    //大数的n次方运算
	int    operator%(const int  &) const;    //大数对一个int类型的变量进行取模运算    
	bool   operator>(const BigNum & T)const;   //大数和另一个大数的大小比较
	bool   operator>(const int & t)const;      //大数和一个int类型的变量的大小比较

	void print();       //输出大数
}; 
BigNum::BigNum(const int b)     //将一个int类型的变量转化为大数
{ 
	int c,d = b;
	len = 0;
	memset(a,0,sizeof(a));
	while(d > MAXN)
	{
		c = d - (d / (MAXN + 1)) * (MAXN + 1); 
		d = d / (MAXN + 1);
		a[len++] = c;
	}
	a[len++] = d;
}
BigNum::BigNum(const char*s)     //将一个字符串类型的变量转化为大数
{
	int t,k,index,l,i;
	memset(a,0,sizeof(a));
	l=strlen(s);   
	len=l/DLEN;
	if(l%DLEN)
		len++;
	index=0;
	for(i=l-1;i>=0;i-=DLEN)
	{
		t=0;
		k=i-DLEN+1;
		if(k<0)
			k=0;
		for(int j=k;j<=i;j++)
			t=t*10+s[j]-'0';
		a[index++]=t;
	}
}
BigNum::BigNum(const BigNum & T) : len(T.len)  //拷贝构造函数
{ 
	int i; 
	memset(a,0,sizeof(a)); 
	for(i = 0 ; i < len ; i++)
		a[i] = T.a[i]; 
} 
BigNum & BigNum::operator=(const BigNum & n)   //重载赋值运算符，大数之间进行赋值运算
{
	int i;
	len = n.len;
	memset(a,0,sizeof(a)); 
	for(i = 0 ; i < len ; i++) 
		a[i] = n.a[i]; 
	return *this; 
}
istream& operator>>(istream & in,  BigNum & b)   //重载输入运算符
{
	char ch[MAXSIZE*4];
	int i = -1;
	in>>ch;
	int l=strlen(ch);
	int count=0,sum=0;
	for(i=l-1;i>=0;)
	{
		sum = 0;
		int t=1;
		for(int j=0;j<4&&i>=0;j++,i--,t*=10)
		{
			sum+=(ch[i]-'0')*t;
		}
		b.a[count]=sum;
		count++;
	}
	b.len =count++;
	return in;

}
ostream& operator<<(ostream& out,  BigNum& b)   //重载输出运算符
{
	int i;  
	cout << b.a[b.len - 1]; 
	for(i = b.len - 2 ; i >= 0 ; i--)
	{ 
		cout.width(DLEN); 
		cout.fill('0'); 
		cout << b.a[i]; 
	} 
	return out;
}

BigNum BigNum::operator+(const BigNum & T) const   //两个大数之间的相加运算
{
	BigNum t(*this);
	int i,big;      //位数   
	big = T.len > len ? T.len : len; 
	for(i = 0 ; i < big ; i++) 
	{ 
		t.a[i] +=T.a[i]; 
		if(t.a[i] > MAXN) 
		{ 
			t.a[i + 1]++; 
			t.a[i] -=MAXN+1; 
		} 
	} 
	if(t.a[big] != 0)
		t.len = big + 1; 
	else
		t.len = big;   
	return t;
}
BigNum BigNum::operator-(const BigNum & T) const   //两个大数之间的相减运算 
{  
	int i,j,big;
	bool flag;
	BigNum t1,t2;
	if(*this>T)
	{
		t1=*this;
		t2=T;
		flag=0;
	}
	else
	{
		t1=T;
		t2=*this;
		flag=1;
	}
	big=t1.len;
	for(i = 0 ; i < big ; i++)
	{
		if(t1.a[i] < t2.a[i])
		{ 
			j = i + 1; 
			while(t1.a[j] == 0)
				j++; 
			t1.a[j--]--; 
			while(j > i)
				t1.a[j--] += MAXN;
			t1.a[i] += MAXN + 1 - t2.a[i]; 
		} 
		else
			t1.a[i] -= t2.a[i];
	}
	t1.len = big;
	while(t1.a[len - 1] == 0 && t1.len > 1)
	{
		t1.len--; 
		big--;
	}
	if(flag)
		t1.a[big-1]=0-t1.a[big-1];
	return t1; 
} 

BigNum BigNum::operator*(const BigNum & T) const   //两个大数之间的相乘运算 
{ 
	BigNum ret; 
	int i,j,up; 
	int temp,temp1;   
	for(i = 0 ; i < len ; i++)
	{ 
		up = 0; 
		for(j = 0 ; j < T.len ; j++)
		{ 
			temp = a[i] * T.a[j] + ret.a[i + j] + up; 
			if(temp > MAXN)
			{ 
				temp1 = temp - temp / (MAXN + 1) * (MAXN + 1); 
				up = temp / (MAXN + 1); 
				ret.a[i + j] = temp1; 
			} 
			else
			{ 
				up = 0; 
				ret.a[i + j] = temp; 
			} 
		} 
		if(up != 0) 
			ret.a[i + j] = up; 
	} 
	ret.len = i + j; 
	while(ret.a[ret.len - 1] == 0 && ret.len > 1)
		ret.len--; 
	return ret; 
} 
BigNum BigNum::operator/(const int & b) const   //大数对一个整数进行相除运算
{ 
	BigNum ret; 
	int i,down = 0;   
	for(i = len - 1 ; i >= 0 ; i--)
	{ 
		ret.a[i] = (a[i] + down * (MAXN + 1)) / b; 
		down = a[i] + down * (MAXN + 1) - ret.a[i] * b; 
	} 
	ret.len = len; 
	while(ret.a[ret.len - 1] == 0 && ret.len > 1)
		ret.len--; 
	return ret; 
}
int BigNum::operator %(const int & b) const    //大数对一个int类型的变量进行取模运算    
{
	int i,d=0;
	for (i = len-1; i>=0; i--)
	{
		d = ((d * (MAXN+1))% b + a[i])% b;  
	}
	return d;
}
BigNum BigNum::operator^(const int & n) const    //大数的n次方运算
{
	BigNum t,ret(1);
	int i;
	if(n<0)
		exit(-1);
	if(n==0)
		return 1;
	if(n==1)
		return *this;
	int m=n;
	while(m>1)
	{
		t=*this;
		for( i=1;i<<1<=m;i<<=1)
		{
			t=t*t;
		}
		m-=i;
		ret=ret*t;
		if(m==1)
			ret=ret*(*this);
	}
	return ret;
}
bool BigNum::operator>(const BigNum & T) const   //大数和另一个大数的大小比较
{ 
	int ln; 
	if(len > T.len)
		return true; 
	else if(len == T.len)
	{ 
		ln = len - 1; 
		while(a[ln] == T.a[ln] && ln >= 0)
			ln--; 
		if(ln >= 0 && a[ln] > T.a[ln])
			return true; 
		else
			return false; 
	} 
	else
		return false; 
}
bool BigNum::operator >(const int & t) const    //大数和一个int类型的变量的大小比较
{
	BigNum b(t);
	return *this>b;
}

void BigNum::print()    //输出大数
{ 
	int i;   
	cout << a[len - 1]; 
	for(i = len - 2 ; i >= 0 ; i--)
	{ 
		cout.width(DLEN); 
		cout.fill('0'); 
		cout << a[i]; 
	} 
	cout << endl;
}
int main(void)
{
	int i,n;
	BigNum x[101];      //定义大数的对象数组
	x[0]=1;
	for(i=1;i<101;i++)
		x[i]=x[i-1]*(4*i-2)/(i+1);
	while(scanf("%d",&n)==1 && n!=-1)
	{
		x[n].print();
	}
}

/* KMP */
void calc() {
    ans = 0;
    memset(p, 0, sizeof(p));
    p[0] = -1;
    int lenw = strlen(w), lent = strlen(t);
    for (int i = 1, j = -1; i < lenw; ++i) {
        for (; j >= 0 && w[j + 1] != w[i]; j = p[j]);
        if (w[j + 1] == w[i]) {
            ++j;
        }
        p[i] = j;
    }
    for (int i = 0, j = -1; i < lent; ++i) {
        for (; j >= 0 && w[j + 1] != t[i]; j = p[j]);
        if (w[j + 1] == t[i]) {
            ++j;
        }
        if (j == lenw - 1) {
            ++ans;
            j = p[j];
        }
    }
    printf("%d\n", ans);
}

/* Convex Hull */

inline double dis(point a, point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline double cross(double x1, double y1, double x2, double y2)
{
	return x1 * y2 - x2 * y1;
}
inline double isleft(point a, point b, point c)
{
	return cross(b.x - a.x, b.y - a.y, c.x - b.x, c.y - b.y);
}

void calc_convex() {
    int i;
    qsort(p + 1, n, sizeof(p[0]), cmp);
	bot=n,top=n+1;
	ans[top++]=1;
	ans[top++]=2;
	for(i=3;i<=n;++i)
	{
		if(isleft(p[ans[top-2]],p[ans[top-1]],p[i])!=0)
		{
			ans[top++]=ans[bot--]=i;
			break;
		}
		ans[top-1]=i;
	}
	if(isleft(p[ans[top-3]],p[ans[top-2]],p[ans[top-1]])<0)
		swap(ans[top-3],ans[top-2]);
	for(++i;i<=n;++i)
	{
		if(isleft(p[ans[bot+1]],p[ans[bot+2]],p[i])>0&&
		   isleft(p[ans[top-2]],p[ans[top-1]],p[i])>0)
			continue;
		while(isleft(p[ans[top-2]],p[ans[top-1]],p[i])<=0) --top;
		ans[top++]=i;
		while(isleft(p[ans[bot+1]],p[ans[bot+2]],p[i])<=0) ++bot;
		ans[bot--]=i;
	}
}

/* Binary Index Tree */

inline int lowbit (int x) {
    return x & -x;
}

int getsum (int x) {
    int res = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) {
        res += bit[i];
    }
    return res;
}

void add(int x, int amount) {
    for (int i = x; i <= 32001; i += lowbit(i)) {
        bit[i] += amount;
    }
}

/* minimal heap */
#include <vector>
#include <algorithm>
vector<int> v;
make_heap(v.begin(), v.end(), greater<int>());
x = v.front();pop_heap(v.begin(), v.end(), greater<int>()); v.pop_back();
v.push_back(x); push_heap(v.begin(), v.end(), greater<int>());

/* map */
#include <map>
map<string, string> dict;
dict[string(s2)] = string(s1);
