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
const int maxn=3010,mod=998244353;
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
bool mem1;
int n;
char a[maxn];
int nx[maxn][2][2];
struct hsh{
    size_t operator()(const pii &x)const{return ((ll)x.fi<<20)|x.se;}
};
unordered_set<pii,hsh> st[maxn];
int f[maxn][maxn],c[maxn];
bool s[maxn],en[maxn];
bool mem2;
void matt(int _cases){
    for(int i=0;i<=n+1;i++)for(int j=0;j<=n+1;j++)f[i][j]=0;
    for(int i=0;i<=n;i++)   st[i].clear();
    scanf("%d%s",&n,a+1);
    for(int i=1;i<=n;i++)s[i]=s[i-1]^(a[i]=='1');
    for(int i=1;i<=n;i++)c[i]=c[i-1]+(a[i]=='?');
    for(int i=0;i<=n+1;i++){
        mems(nx[i],0);
        auto trans=[&](int x,int y,int w){if(!nx[i][x][y])nx[i][x][y]=w;};
        for(int j=i+1;j<=n;j++)if((c[j-1]^c[i])||(s[j-1]==s[i])){
            if(a[j]=='0'||a[j]=='?')    trans(0,s[j],j);
            if(a[j]=='1'||a[j]=='?')    trans(1,s[j],j);
        }
        for(int j:{0,1})for(int k:{0,1})if(!nx[i][j][k])nx[i][j][k]=n+1;
        en[i]=(s[n]==s[i])||(c[n]^c[i]);
    }
    en[n+1]=0;
    int ans=0;
    en[0]=c[n]||!s[n];
    f[0][n+1]=1;st[0].ep(0,n+1);
    for(int _=0;_<=n;_++){
        for(auto [i,j]:st[_]){
            if(en[i]||en[j])    madd(ans,f[i][j]);
            for(int c:{0,1}){
                int k=min(nx[i][c][0],nx[j][c][0]),l=min(nx[i][c][1],nx[j][c][1]);
                if(k<=n||l<=n){
                    madd(f[k][l],f[i][j]);
                    st[min(k,l)].ep(k,l);
                }
            }
        }
    }
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}