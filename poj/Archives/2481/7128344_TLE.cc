#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

struct P
{
    int x, y, id;
};
P p[100005];
int n, a[100005], maxx, b[100005];

//事实上，当排好序后，从后到前计算，前面的将不会影响后面的，每一个数组的可以变成是[x, maxx]，加入这条线段
//每次计算时，将会计算(0, x]里有的线段
//一个数每一次增大，步长每次都增大
//一个数每一次减小，步长每次都减小
//可以证明，一个大数减小过程中与一个小数增大过程中，相遇有且只有一次

int lowbit(int k)    //6 & (-6) == 2, 10 & (-10) == 2, 9 & (-9) == 1
{
    //计算机里是补码表示的，所以比如-1就是全1，正负数除了最高的符号位不一样外，最低个1位以前的全部取反
    return k & (-k);
}

void Modify(int num, int v)
{
    while(num <= maxx)
    {
        a[num] += v;
        num += lowbit(num);
    }
}

int Sum(int num)
{
    int ans = 0;
    if(num <= 0)
        return 0;
    while(num)
    {
        ans += a[num];
        num -= lowbit(num);
    }
    return ans;
}

bool operator < (const P a, const P b)    //排序后使得前面的不可能盖住后面的
{
    if(a.y != b.y)
        return a.y < b.y;
    else
        return a.x > b.x;
}

void Init()
{
    int i;
    maxx = 0;
    for(i=0; i<n; i++)
    {
        scanf("%d%d", &p[i].x, &p[i].y);
        p[i].id = i;
        p[i].x++;                //从1开始的
        p[i].y++;
        if(p[i].y > maxx)
            maxx = p[i].y;
    }
    memset(a, 0, sizeof(a));
}

void Print()
{
    int i;
    for(i=0; i<n; i++)
    {
        printf("%d",b[i]);
        if(i<n-1) printf(" ");
		else printf("\n"); 
    }
}

int main()
{
    int i;
    while(scanf("%d",&n) && n)
    {
        Init();
        sort(p, p+n);
        for(i=n-1; i>=0; i--)
        {
            if(i != n-1 && p[i].y == p[i+1].y && p[i].x == p[i+1].x)    //如果相同
                b[p[i].id] = b[p[i+1].id];
            else
                b[p[i].id] = Sum(p[i].x);
            Modify(p[i].x, 1);
        }
        Print();
    }
    return 0;
}
