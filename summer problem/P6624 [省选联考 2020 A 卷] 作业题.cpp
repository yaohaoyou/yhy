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
const int maxn=35,V=2e5,mod=998244353;
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
struct func{
    int k,b;
    func(int _k=0,int _b=0){k=_k;b=_b;}
    inline func operator-(func y){return func(imdel(k,y.k),imdel(b,y.b));}
    inline void operator-=(func y){*this=*this-y;}
    inline func operator+(func y){return func(imadd(k,y.k),imadd(b,y.b));}
    inline void operator+=(func y){*this=*this+y;}
    inline func operator*(func y){return func(imadd(immul(k,y.b),immul(b,y.k)),immul(b,y.b));}
    inline func operator/(func y){int iv=qpow(y.b,mod-2);return func(1ull*imdel(immul(k,y.b),immul(b,y.k))*iv%mod*iv%mod,immul(b,iv));}
    inline void print(){printf("(%dx + %d) ",k,b);}
};
int n,m;
int phi[V+10];
bool ntp[V+10];
vector<int> p;
vector<piii> E[V+10];
func a[maxn][maxn];
void init(){
    phi[1]=1;
    for(int i=2;i<=V;i++){
        if(!ntp[i]) p.eb(i),phi[i]=i-1;
        for(int j:p){
            if(1ll*i*j>V)   break;
            ntp[i*j]=true;
            if(i%j==0){phi[i*j]=phi[i]*j;break;}
            else    phi[i*j]=phi[i]*phi[j];
        }
    }
}
func det(auto a){
    n--;
    int res=1;
    for(int i=1;i<=n;i++){
        if(!a[i][i].b){
            for(int j=i+1;j<=n;j++)if(a[j][i].b){
                swap(a[i],a[j]);res*=-1;
                break;
            }
        }
        for(int j=i+1;j<=n;j++){
            if(a[j][i].b){
                func x=a[j][i]/a[i][i];
                // a[i][i].print();a[j][i].print();(x*a[i][i]).print();puts("");
                // printf("%d %d\n",i,j);
                for(int k=i;k<=n;k++)   a[j][k]=a[j][k]-x*a[i][k];
            }
        }
    }
    func ans(0,1);
    for(int i=1;i<=n;i++)ans=ans*a[i][i];
    if(!~res)   ans=ans*func(0,mod-1);
    n++;
    return ans;
}
int main(){
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        for(int d=1;d<=w;d++)if(w%d==0)E[d].eb(pii(u,v),w);
    }
    int ans=0;
    for(int i=1;i<=V;i++){
        if(E[i].size()<n-1)    continue;
        for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)a[j][k]=func();
        for(auto [e,w]:E[i]){
            auto [u,v]=e;
            a[u][v]-=func(w,1),a[v][u]-=func(w,1);
            a[u][u]+=func(w,1),a[v][v]+=func(w,1);
        }
        madd(ans,immul(phi[i],det(a).k));
    }
    printf("%d\n",ans);
}