#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=6e5+10,mod=1e9+7;
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
int n,q;
int a[maxn];
piii Q[maxn];
int ans[maxn];
int fac[maxn],inv[maxn];
int f[maxn],g[maxn];
vector<pii> vl[maxn],vr[maxn];
int Log[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x){gmx(tr[x],s);x^=lowbit(x);}}
    inline int que(int x){int res=0;while(x<=n){gmx(res,tr[x]);x+=lowbit(x);}return res;}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
struct ST{
    int st[20][maxn];
    void build(){
        for(int i=2;i<=n;i++)Log[i]=Log[i>>1]+1;
        memc(st[0],a);
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int query(int l,int r){int k=Log[r-l+1];return l>r?-1e9:max(st[k][l],st[k][r-(1<<k)+1]);}
}mx,mn;
void init(){
    const int N=6e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
stack<int> stk;
map<int,vector<int>> mp;
bool mem2;
int main(){
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    scanf("%d",&q);
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&a[stk.top()]<a[i])  stk.pop();
        f[i]=stk.empty()?0:stk.top();
        stk.ep(i);
    }
    stack<int>().swap(stk);
    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()]>a[i])  stk.pop();
        g[i]=stk.empty()?n+1:stk.top();
        stk.ep(i);
        vl[f[i]].eb(g[i],q+1);
        // vl[g[i]].eb(i,-(q+1));
    }
    mx.build();
    for(int i=1;i<=n;i++)a[i]=-a[i];
    mn.build();
    for(int i=1;i<=n;i++)a[i]=-a[i];
    for(int i=1;i<=q;i++){
        int l,r;scanf("%d%d",&l,&r);
        vl[l].eb(r,i);
        int k=r-l+1,m=mx.query(l,r);
        vr[r].eb(l,i);
        ans[i]=imdel(C(n+n-m-k,n-k),C(n+n-m-k,n-m-1));
    }
    for(int i=1;i<=n;i++){
        sort(vl[i].begin(),vl[i].end(),[&](pii x,pii y){return x.se<y.se;});
        for(auto [j,k]:vl[i]){
            if(k<=q){
                mp[j].eb(k);
            }
            else if(!mp.empty()){
                auto it=prev(mp.end());
                while(true){
                    if(it->fi<j){it++;break;}
                    for(int x:it->se)   ans[x]=0;
                    if(it==mp.begin())  break;
                    it--;
                }
                while(it!=mp.end()) it=mp.erase(it);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(f[i])    T.add(f[i],a[i]);
        for(auto [l,id]:vr[i]){
            int x=min(-mn.query(1,l-1),-mn.query(i+1,n));
            if(T.que(l)>x)  ans[id]=0;
        }
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}