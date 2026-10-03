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
bool mem1;
const int maxn=5e5+10,mod=1e9+7;
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
int a[maxn],mn[maxn];
int f[2][40][40];
bool ntp[maxn];
vector<int> p;
unordered_map<int,int> fac;
unordered_map<int,vector<int>> v;
void init(){
    n=5e5;
    for(int i=2;i<=n;i++){
        if(!ntp[i]) p.eb(i),mn[i]=i;
        for(int j:p){
            if(1ll*i*j>n)   break;
            if(!mn[i*j])    mn[i*j]=j;
            ntp[i*j]=true;
            if(i%j==0)  break;
        }
    }
}
void matt(int _cases){
    fac.clear();v.clear();
    scanf("%d%d",&n,&m);
    {
        int x=m;
        while(x^1){
            int c=0,y=mn[x];
            while(mn[x]==y)c++,x/=mn[x];
            fac[y]=c;
        }
    }
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        int x=a[i];
        while(x^1){
            int c=0,y=mn[x];
            while(mn[x]==y)c++,x/=mn[x];
            v[y].eb(c);
        }
    }
    int ans=1;
    for(auto [i,j]:fac)if(v.find(i)==v.end())return puts("0"),void();
    for(auto [d,vec]:v){
        int mx=*max_element(vec.begin(),vec.end()),p=fac[d];
        mems(f[0],0);f[0][0][0]=1;
        for(int i=1;i<=vec.size();i++){
            mems(f[i&1],0);
            for(int j=0;j<=mx;j++){
                for(int s=0;s<=j+p;s++){
                    for(int k=0;k<=vec[i-1]&&s+k<=max(j,k)+p;k++)    madd(f[i&1][max(j,k)][s+k],f[(i-1)&1][j][s]);
                }
            }
        }
        int res=0;
        for(int i=0;i<=mx;i++)  madd(res,f[vec.size()&1][i][i+p]);
        mmul(ans,res);
    }
    printf("%d\n",ans);
}
bool mem2;
int main(){debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);init();int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}