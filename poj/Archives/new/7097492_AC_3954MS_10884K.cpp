#include<iostream>
//#include
//#include
using namespace std;
//经典的最小割 我跑的很慢，将近4s，sap直接挂了
const int maxn=20005;
const int maxm=1200005;
const int INF=100000000;
inline int min(int x,int y){return x<y?x:y;}
int d[maxn],q[maxn],st[maxn],top,len;
typedef struct node
{
    int v,flow;
    node *next;
    node *rev();   
    }node;
node edge[maxm],*adj[maxn],*cur[maxn],*pre[maxn];
node inline *node::rev(){return edge+((this-edge)^1);}
inline void addedge(int u,int v,int flow)
{
    edge[len].v=v;edge[len].flow=flow;
    edge[len].next=adj[u];adj[u]=&edge[len++];
    }
inline void insert(int u,int v,int flow)
{
    addedge(u,v,flow);
    addedge(v,u,0);
    }
bool bfs(int n,int s,int t)//找增广
{
    int i,u,v,head=0,tail=0;q[tail++]=s;
    fill(d,d+n,-1);
    node *p;d[s]=0;
    while(head<tail)
    {
          for(u=q[head++],p=adj[u];p;p=p->next)
          {
              v=p->v;
              if(d[v]==-1&&p->flow>0)
              {
                 d[v]=d[u]+1;
                 q[tail++]=v;
                 if(v==t)return 1;                   
                 }                                
              }         
          }
    return 0;     
    }
int dinic(int n,int s,int t)
{
    int i,u,v,tmp,maxflow=0;
    while(bfs(n,s,t))
    {
          st[top=1]=u=s;
          for(i=0;i<n;i++)cur[i]=adj[i];
          while(cur[s])
          {
                if(u!=t&&cur[u]&&cur[u]->flow>0&&d[u]+1==d[cur[u]->v]){v=cur[u]->v;st[++top]=v;pre[v]=cur[u];u=v;}
                else if(u==t)
                {
                    for(tmp=INF,i=top;i>1;i--)tmp=min(tmp,pre[st[i]]->flow);
                    for(maxflow+=tmp,i=top;i>1;i--)
                    {
                        pre[st[i]]->flow-=tmp;
                        pre[st[i]]->rev()->flow+=tmp;
                        if(pre[st[i]]->flow==0)top=i-1;
                        }
                    u=st[top];
                    }
                else
                {
                    while(u!=s&&cur[u]==NULL)u=st[--top];
                    cur[u]=cur[u]->next;
                    }
                }
          }
    return maxflow;
    }                    
int main()
{
    int i,j,k,u,v,n,s,t,m,flow;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
          s=n;t=n+1;len=0;
          for(i=0;i<=n+1;i++)adj[i]=0;
          for(i=1;i<=n;i++)
          {
              scanf("%d%d",&u,&v);
              insert(s,i-1,u);
              insert(i-1,t,v);            
              }              
          for(i=1;i<=m;i++)
          {
              scanf("%d%d%d",&u,&v,&flow);
              insert(u-1,v-1,flow);
              insert(v-1,u-1,flow);            
              }             
          n+=2;
          printf("%d\n",dinic(n,s,t));   
          }
    return 0;
    } 
