#include<bits/stdc++.h>
#define ll long long
#define int long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10;
const ll INF=1e18;
int n;
ll C;
struct node{ll x,y,w;}a[maxn];
ll dp[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;

inline void gmx(int &x,int y){(x<y)&&(x=y);}
inline void gmn(int &x,int y){(x>y)&&(x=y);}
// inline void gmx(ll &x,ll y){(x<y)&&(x=y);}
// inline void gmn(ll &x,ll y){(x>y)&&(x=y);}
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tot;
    int root[maxn],lc[maxn*20],rc[maxn*20];
    ll tr[maxn*20];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    void upd(int &p,int q,int l,int r,int x,ll s){
        p=++tot;
        ls=lc[q];rs=rc[q];tr[p]=max(tr[q],s);
        if(l==r)    return;
        setmid;(x<=mid)?upd(ls,lc[q],l,mid,x,s):upd(rs,rc[q],mid+1,r,x,s);pu(p);
    }
    ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;ll ret=-INF;if(pl<=mid)ret=query(lson,pl,pr);if(pr>mid)gmx(ret,query(rson,pl,pr));return ret;}
    #undef ls
    #undef rs
}
using namespace SegmentTree;
unordered_map<ll,ll> LL,RR,mp;
stack<int> stk;
int ls[maxn],rs[maxn];
ll L[maxn],R[maxn];
void dfs(int u,int ft){
    if(ls[u])   dfs(ls[u],u);
    dp[u]=dp[u-1];
    if(L[u]<u)  gmx(dp[u],query(root[ft],1,n,L[u],u-1)+a[u].w-a[u].x+C);
    upd(root[u],root[ft],1,n,u,a[u].x-a[u].w+dp[u]);
    // printf("(%d,%d,%d)\n",a[u].x,a[u].y,a[u].w);
    // printf("dp[%d] = %d\n",u,dp[u]);
    if(rs[u])   dfs(rs[u],u);
}
main(){
    // data();
    n=read();C=readll();
    for(int i=1;i<=n;i++)   a[i].x=readll(),a[i].y=readll(),a[i].w=readll();
    sort(a+1,a+n+1,[&](node x,node y){return x.x<y.x;});
    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()].y<a[i].y)  stk.pop();
        RR[a[i].y]=stk.empty()?-1:a[stk.top()].y;
        // printf("%d %d\n",a[i].y,RR[a[i].y]);
        stk.ep(i);
    }
    stack<int>().swap(stk);
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&a[stk.top()].y>a[i].y)  stk.pop();
        LL[a[i].y]=stk.empty()?-1:a[stk.top()].y;
        // printf("%d %d\n",a[i].y,LL[a[i].y]);
        stk.ep(i);
    }
    sort(a+1,a+n+1,[&](node x,node y){return x.y<y.y;});
    for(int i=1;i<=n;i++)   mp[a[i].y]=i;
    for(int i=1;i<=n;i++)   L[i]=(~LL[a[i].y])?mp[LL[a[i].y]]:1,R[i]=(~RR[a[i].y])?mp[RR[a[i].y]]:n;
    // for(int i=1;i<=n;i++)   printf("%d %d %d\n",a[i].x,a[i].y,a[i].w);
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        // printf("%d %d\n",L[i],R[i]);
        for(int j=i-1;j>=L[i];j--){
            if(R[j]>=i&&a[i].x>a[j].x){             
                gmx(dp[i],dp[j-1]+a[i].w-a[j].w-a[i].x+a[j].x+C);
                // printf("[%d,%d] %d\n",j,i,dp[j-1]+a[i].w-a[j].w-a[i].x+a[j].x+C);
            }
        }
        // printf("dp[%d] = %lld\n",i,dp[i]);
    }
    // puts("");
    // int rt;
    // for(int i=1;i<=n;i++){
    //     int x=0;
    //     while(!stk.empty()&&a[stk.top()].y>a[i].y){x=stk.top();stk.pop();}
    //     if(!stk.empty())    ls[i]=rs[stk.top()],rs[stk.top()]=i;
    //     else    rt=i,ls[i]=x;
    //     stk.ep(i);
    // }
    // tr[0]=-INF;
    // dfs(rt,0);
    printf("%lld\n",dp[n]);
}