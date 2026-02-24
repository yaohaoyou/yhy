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
const int maxn=4e5+10,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,tot;
int a[maxn];
pii b[maxn];
int s[maxn];
vector<int> son[maxn];
int fac[maxn],inv[maxn];
stack<int> stk;
bool dir[maxn];
void init(){
    const int N=4e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int cat(int x){return imdel(C(x+x,x),C(x+x,x-1));}
void dfs(int u,int ft){s[u]=son[u].size();for(int t:son[u])dfs(t,u);if(ft&&u>n&&dir[u]==dir[ft])s[ft]+=s[u]-1,s[u]=0;}
int main(){
    freopen("random.in","r",stdin);freopen("random.out","w",stdout);
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    tot=n;
    for(int i=1;i<=n;i++){
        b[i]=pii(a[i],a[i]);int now=i;
        while(!stk.empty()){
            int x=stk.top();bool d;
            if(b[x].se==b[now].fi-1)    b[x].se=b[now].se,d=true;
            else if(b[x].fi==b[now].se+1)   b[x].fi=b[now].fi,d=false;
            else break;
            // printf("%d %d\n",tot+1,x);printf("%d %d\n",tot+1,now);
            tot++;son[tot].eb(x);son[tot].eb(now);b[tot]=b[x];now=tot;dir[tot]=d;stk.pop();
        }
        stk.ep(now);
    }
    // for(int i=1;i<=tot;i++) printf("%d ",dir[i]);puts("");
    if(stk.size()>1) return puts("0"),0;
    dfs(stk.top(),0);
    int ans=1;
    for(int i=1;i<=tot;i++)if(s[i]){
        mmul(ans,cat(s[i]-1));
        // printf("%d %d\n",i,s[i]);
    }
    printf("%d\n",ans);
}