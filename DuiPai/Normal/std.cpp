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
const int maxn=1e6+10;
int mod;
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
int n;
int f[maxn][2],dep[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,as1,as2;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v,1,1};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
struct Matrix{
    int a[2][2];
    inline void clear(){mems(a,0);}
    inline void init(){clear();a[0][0]=a[1][1]=1;}
    inline int* operator[](int x){return a[x];}
    Matrix operator*(Matrix x)const{
        Matrix res;res.clear();
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    madd(res.a[i][j],immul(a[i][k],x.a[k][j]));
        return res;
    }
    inline void print(){printf("%d %d\n%d %d\n",a[0][0],a[0][1],a[1][0],a[1][1]);}
};
Matrix pre[maxn],suf[maxn];
void dfs(int u,int ft){
    dep[u]=dep[ft]+1;
    f[u][0]=f[u][1]=0;
    if(dep[u]&1)   f[u][0]=1;
    else    f[u][1]=1;
    vector<int> son;son.clear();go(u,i)if(t^ft)son.eb(t);
    Matrix now;now.init();
    for(int t:son){
        dfs(t,u);
        int f0=f[u][0],f1=f[u][1];
        if(dep[u]&1){
            madd(f[u][1],immul(imadd(f1,f0),f[t][1]));
            madd(f[u][1],immul(f1,f[t][0]));
            madd(f[u][0],immul(f0,f[t][0]));
        }
        else{
            madd(f[u][1],immul(f1,f[t][1]));
            madd(f[u][0],immul(imadd(f0,f1),f[t][0]));
            madd(f[u][0],immul(f0,f[t][1]));
        }
        if(!ft){
            Matrix M;
            M[0][0]=imadd(f[t][0],1);M[0][1]=f[t][1];
            M[1][0]=0;M[1][1]=imadd(f[t][0],imadd(f[t][1],1));
            pre[t]=now;now=now*M;
        }
    }
    if(!ft){
        now.init();
        reverse(son.begin(),son.end());
        for(int t:son){
            Matrix M;
            M[0][0]=imadd(f[t][0],1);M[0][1]=f[t][1];
            M[1][0]=0;M[1][1]=imadd(f[t][0],imadd(f[t][1],1));
            suf[t]=now;now=M*now;
        }
    }
}
int main(){
    // freopen("game.in","r",stdin);freopen("game.out","w",stdout);
    scanf("%d%d",&n,&mod);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    Matrix Matt;Matt.clear();Matt[0][0]=1;Matt[0][1]=0;
    for(int u=1;u<=n;u++){
        dfs(u,0);
        // printf("%d : %d %d\n",u,f[u][0],f[u][1]);
        go(u,i){
            // int f0=immul(f[u][0],qpow(f[t][0]+1,mod-2)),f1=imdel(f[u][1],immul(f0,f[t][1]));
            // mmul(f1,qpow(f[t][1]+1,mod-2));
            Matrix tmp=(Matt*pre[t]*suf[t]);
            mmul(e[i|1].as1,tmp.a[0][1]);
            mmul(e[i|1].as2,tmp.a[0][0]);
        }
    }
    int ans=0;
    for(int i=3;i<=cnt;i+=2)    madd(ans,imadd(e[i].as1,e[i].as2));
    printf("%d\n",ans%mod);
}