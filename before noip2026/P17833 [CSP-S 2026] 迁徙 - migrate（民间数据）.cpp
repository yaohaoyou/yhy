#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pil pair<int,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) fill(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e6+10;
bool mem1;
int n;ll d;
ll a[maxn];
int ls[maxn],rs[maxn],dw[23][maxn];
bool lian[maxn];
int dep[maxn],son[maxn],siz[maxn];
ll f[maxn],g[maxn];
int num[maxn];
ll dfs(int u,bool o,int d){
    if(!d)fll(num,0,n);
    num[d]++;if(num[d]>2)return 0;
    ll res=0;if(o)res=son[u];
    if(rs[u])   res+=dfs(rs[u],o,d+1);
    if(!o&&ls[u])   res+=dfs(ls[u],1,d+1);
    return res;
}
inline void calc(int u){
    if(ls[u]&&rs[u]){
        f[u]=f[rs[u]]+son[ls[u]];lian[u]=0;
        g[u]=son[rs[u]]+g[rs[u]];
        dep[u]=dep[rs[u]]+1;
        siz[u]=siz[rs[u]]+siz[ls[u]]+1;
        int x=dep[ls[u]];
        if(!rs[rs[u]])  f[u]+=g[ls[u]];
    }
    else if(rs[u]){
        siz[u]=1+siz[rs[u]];dep[u]=dep[rs[u]]+1;
        lian[u]=lian[rs[u]];f[u]=f[rs[u]];
        g[u]=son[rs[u]]+g[rs[u]];
    }
    else{
        assert(!ls[u]&&!rs[u]);
        siz[u]=1;
        lian[u]=true;f[u]=dep[u]=g[u]=0;
    }
}
bool mem2;
void matt(int _cases){
    fll(dep,0,n);fll(son,0,n);fll(lian,0,n);fll(ls,0,n);fll(rs,0,n);fll(f,0,n);fll(g,0,n);
    cin>>n>>d;
    for(int i=1;i<=n;i++)   cin>>a[i];
    ll ans=0;
    siz[1]=lian[1]=1;
    for(int i=1,j=1;i<=n;i++){
        while(j<=n&&a[j]<a[i]-d)j++;
        if(j==i){siz[i]=lian[i]=1;continue;}
        son[i-1]-=i-j-1;
        son[i]=i-j;
        if(j==i-1)  rs[i]=j,calc(i);
        else{
            ls[i]=j+1;rs[i]=j;
            bool fl=false;
            if(ls[i-1]==j||ls[i-1]==j+1)    ls[i-1]=0,fl=true;
            if(rs[i-1]==j||rs[i-1]==j+1)    rs[i-1]=0,fl=true;
            if(fl)  calc(i-1);
            calc(i);
        }
        ans+=f[i];
    }
    cout<<ans<<'\n';
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int C,T;cin>>C>>T;for(int i=1;i<=T;i++)matt(i);
}