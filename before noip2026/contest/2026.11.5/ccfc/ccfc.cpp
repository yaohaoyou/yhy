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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10,inf=1e9;
int n;
char s[maxn];
int sa[2][maxn],rk[2][maxn],ht[2][maxn],y[maxn],buc[maxn];
int nx[maxn];
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline void upd(int l,int r,int s){if(l<=r)add(l,s),add(r+1,-s);}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
struct ST{
    int len;
    int st[21][maxn<<1];
    void build(int *arr){
        st[0][++len]=inf;
        for(int i=2;i<=n;i++)   st[0][++len]=arr[i],st[0][++len]=inf;
        for(int i=1;i<=20;i++)for(int j=1;j<=len;j++)st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int query(int l,int r){int k=31^__builtin_clz(r-l+1);return min(st[k][l],st[k][r-(1<<k)+1]);}
}st[2];
void build_SA(bool o){
    int m='z';
    mems(buc,0);
    for(int i=1;i<=n;i++)   buc[rk[o][i]=s[i]]++;
    for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
    for(int i=n;i;i--)  sa[o][buc[rk[o][i]]--]=i;
    for(int w=1;w<=n;w<<=1){
        int p=0;
        for(int i=n-w+1;i<=n;i++)   y[++p]=i;
        for(int i=1;i<=n;i++)if(sa[o][i]>w)y[++p]=sa[o][i]-w;
        mems(buc,0);
        for(int i=1;i<=n;i++)   buc[rk[o][i]]++;
        for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
        for(int i=n;i;i--)  sa[o][buc[rk[o][y[i]]]--]=y[i];
        memc(y,rk[o]);
        rk[o][sa[o][1]]=m=1;
        for(int i=2;i<=n;i++){
            if(y[sa[o][i]]==y[sa[o][i-1]]&&(sa[o][i]+w<=n?y[sa[o][i]+w]:0)==(sa[o][i-1]+w<=n?y[sa[o][i-1]+w]:0))  rk[o][sa[o][i]]=m;
            else    rk[o][sa[o][i]]=++m;
        }
        if(n==m)    break;
    }
    for(int i=1,k=0;i<=n;i++){
        if(rk[o][i]==1)k=0;
        else{
            if(k)k--;
            int x=sa[o][rk[o][i]-1];
            while(i+k<=n&&x+k<=n&&s[i+k]==s[x+k])k++;
            ht[o][rk[o][i]]=k;
        }
    }
    st[o].build(ht[o]);
}
inline int lcp(int x,int y){assert(x^y);x=(rk[0][x]<<1)-1;y=(rk[0][y]<<1)-1;if(x>y)swap(x,y);return st[0].query(x,y);}
inline int lcs(int x,int y){assert(x^y);x=n-x+1;y=n-y+1;x=(rk[1][x]<<1)-1;y=(rk[1][y]<<1)-1;if(x>y)swap(x,y);return st[1].query(x,y);}
int L[maxn],R[maxn],rnk[maxn],tot;
void dfs(int u){
    rnk[L[u]=++tot]=u;
    go(u,i)dfs(t);
    R[u]=tot;
}
vector<pii> v[maxn];
int ans[maxn];
bool mem2;
int main(){
    freopen("ccfc.in","r",stdin);freopen("ccfc.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%s",s+1);n=strlen(s+1);reverse(s+1,s+n+1);
    add(0,1);
    for(int i=2;i<=n;i++){
        int j=nx[i-1];
        while(j&&s[j+1]!=s[i])  j=nx[j];
        j+=(s[j+1]==s[i]);
        nx[i]=j;
        add(nx[i],i);
    }
    dfs(0);
    build_SA(0);
    reverse(s+1,s+n+1);
    build_SA(1);
    reverse(s+1,s+n+1);
    for(int p=1;p<=n/2;p++){
        for(int x=p*3,y=0;x<=n;x+=p){
            int l=x-lcs(x,x-p)+1,r=x+lcp(x,x-p)-1;
            if(l>r||l<=y)continue;
            l+=p-1;gmx(l,p*3+1);
            if(l<=r){
                v[L[p]].eb(l,r);
                v[R[p]+1].eb(l,-r);
            }
            y=x;
            x=r/p*p;
        }
    }
    for(int i=1;i<=n+1;i++){
        for(auto [l,r]:v[i]){
            if(r>0) T.upd(l,r,1);
            else    T.upd(l,-r,-1);
        }
        ans[rnk[i]]=T.que(rnk[i]);
    }
    reverse(ans+1,ans+n+1);
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);
}