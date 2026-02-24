// #pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define if(sth) if(__builtin_expect(sth,1))
#define while(sth) while(__builtin_expect(sth,1))
using namespace std;
const int maxn=1e5+10;
int n,m;
struct node{int t,l,r,c;}a[maxn];
ll dp[maxn];
ll ans;
bool vis[maxn];
priority_queue<pli,vector<pli>,greater<pli>> q;
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<pii> st[maxn<<2];int star[maxn<<2];
    void update(setpos,int x,pii s){
        st[p].eb(s);
        if(l==r)    return;
        setmid;
        if(x<=mid)  update(lson,x,s);
        else    update(rson,x,s);
    }
    void build(setpos){
        stable_sort(st[p].begin(),st[p].end());
        if(l==r)    return;
        setmid;
        build(lson);build(rson);
    }
    void updedge(setpos,int pl,int pr,int u,int s){
        if(l>=pl&&r<=pr){
            int it=star[p];
            while(it<st[p].size()&&st[p][it].fi<=s){
                int v=st[p][it].se;
                if(dp[v]>dp[u]+a[v].c){
                    dp[v]=dp[u]+a[v].c;
                    q.ep(dp[v],v);
                }
                it=++star[p];
            }
            return;
        }
        setmid;
        if(pl<=mid) updedge(lson,pl,pr,u,s);
        if(pr>mid)  updedge(rson,pl,pr,u,s);
    }
}T[2];
void dijkstra(){
    for(int i=1;i<=n;i++)
        if(a[i].l==1)   q.ep(dp[i],i);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])  continue;
        vis[u]=true;
        if(u^1) T[0].updedge(all,1,u-1,u,a[u].r-a[u].t+1);
        if(u^n) T[1].updedge(all,u+1,n,u,a[u].r+a[u].t+1);
    }
}
namespace IO{
    const int SIZ=1000000;
    static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++
    #define putchar(x) (p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
    #define flush fwrite(obuf,p3-obuf,1,stdout)
    #define if(sth) if(__builtin_expect(sth,1))
    #define while(sth) while(__builtin_expect(sth,1))
    #define i128 __int128
    #define ll long long
    inline int read(){
        int x=0; int f=1; char c=getchar();
        while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
        while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getchar();
        x*=f;
        return x;
    }
    inline void printll(ll x){ 
        if(!x)return putchar(48),void();
        int len=0;
        if(x<0)x=-x,putchar(45);
        while(x)cc[len++]=x%10+48,x/=10;
        while(len--)putchar(cc[len]);
    }
}
using namespace IO;
int main(){
    // freopen("D:\\yhy\\GDFZ_yhy\\down\\lai\\lai4.in","r",stdin);
    // freopen("lai.in","r",stdin);freopen("lai.out","w",stdout);
    m=read();n=read();
    for(int i=1;i<=n;i++)   a[i].t=read(),a[i].l=read(),a[i].r=read(),a[i].c=read();
    mems(dp,0x3f);
    ans=dp[0];
    sort(a+1,a+n+1,[&](node x,node y){return x.t<y.t;});
    for(int i=1;i<=n;i++)
        if(a[i].l==1)   dp[i]=a[i].c;
    #pragma unroll(4)
    for(int i=1;i<=n;i++){
        T[0].update(all,i,pii(a[i].l-a[i].t,i));
        T[1].update(all,i,pii(a[i].t+a[i].l,i));
    }
    T[0].build(all);T[1].build(all);
    dijkstra();
    for(int i=1;i<=n;i++)
        if(a[i].r==m) ans=min(ans,dp[i]);
    printll(ans==dp[0]?-1:ans);flush;
}