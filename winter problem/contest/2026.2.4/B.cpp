#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1010,N=1e6,maxm=1e6+10,inf=0x3f3f3f3f;
const int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
struct BIT{
    int tr[maxm];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=N){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
}T;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,N
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxm<<2],tag[maxm<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pt(int p,int s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    inline void upd(int x,int s){
        int p=1,l=1,r=N;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        if(x>1)upd(all,1,x-1,s);
        T.add(x,s);
        int cnt=T.query(x,x);
        if(!cnt) tr[p]=-inf;
        else    tr[p]=T.query(x,N)-1+x;
        while(p>>=1)    pu(p);
    }
    void build(setpos){tr[p]=-inf;if(l==r)return;setmid;build(lson);build(rson);}
}
using namespace SegmentTree;
int n,q;
char a[maxn][maxn];
queue<pii> que;
int d[maxn][maxn];
void bfs(){
    mems(d,0x3f);
    d[1][1]=0;que.ep(1,1);
    while(!que.empty()){
        int x=que.front().fi,y=que.front().se;que.pop();
        for(int i=0;i<4;i++){
            int xx=x+dir[i][0],yy=y+dir[i][1];
            if(xx>0&&xx<=n&&yy>0&&yy<=n&&a[xx][yy]!='#'&&d[xx][yy]==inf){
                d[xx][yy]=d[x][y]+1;
                que.ep(xx,yy);
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%s",a[i]+1);
    bfs();build(all);
    int cnt=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(a[i][j]=='F')upd(d[i][j],1),cnt++;
    printf("%d\n",cnt?tr[1]:0);
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        if(a[x][y]=='F')    upd(d[x][y],-1),a[x][y]='.',cnt--;
        else upd(d[x][y],1),a[x][y]='F',cnt++;
        printf("%d\n",cnt?tr[1]:0);
    }
}