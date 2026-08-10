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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=110,maxm=1010,mod=31011;
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
int n,m;
map<int,vector<pii>> mp;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int a[maxn][maxn];
int id[maxn],bel[maxn];
vector<pii> vv;
unordered_set<int> st;
inline int det(){
    int res=1;
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            while(a[i][i]){
                int x=a[j][i]/a[i][i];
                for(int k=i;k<=m;k++)   mdel(a[j][k],immul(x,a[i][k]));
                swap(a[i],a[j]);res*=-1;
            }
            swap(a[i],a[j]);res*=-1;
        }
    }
    (res==-1)&&(res+=mod);
    for(int i=1;i<=m;i++)   mmul(res,a[i][i]);
    return res;
}
int main(){
    scanf("%d%d",&n,&m);
    U.init();
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);mp[w].eb(u,v);U.merge(u,v);}
    for(int i=1;i<=n;i++)if(U[i]^U[1])return puts("0"),0;
    U.init();
    int ans=1;
    for(auto [_,vec]:mp){
        mems(bel,0);
        vv.clear();st.clear();
        for(auto [u,v]:vec)if(U[u]^U[v])    vv.eb(u,v),st.ep(u),st.ep(v);
        if(vv.empty())  continue;
        int tot=0;
        for(int i:st){
            if(bel[i])  continue;
            bel[i]=++tot;
            for(int j:st)if(!bel[j]&&U[j]==U[i])bel[j]=tot;
        }
        for(auto [u,v]:vv)U.merge(u,v);
        for(auto it=st.begin();it!=st.end();it=st.erase(it)){
            vector<int> V;V.clear();
            for(auto i=next(it);i!=st.end();){
                if(U[*i]==U[*it]){
                    if(bel[*i]!=bel[*it]&&!id[bel[*i]]) V.eb(bel[*i]),id[bel[*i]]=V.size();
                    i=st.erase(i);
                }
                else    i++;
            }
            V.eb(bel[*it]);id[bel[*it]]=V.size();
            mems(a,0);
            for(auto [u,v]:vv)if(id[bel[u]]&&id[bel[v]]){
                u=id[bel[u]];v=id[bel[v]];
                mdel(a[u][v],1);mdel(a[v][u],1);madd(a[u][u],1);madd(a[v][v],1);
            }
            m=V.size()-1;
            mmul(ans,det());
            for(int i:V)    id[i]=0;
        }
    }
    printf("%d\n",ans);
}