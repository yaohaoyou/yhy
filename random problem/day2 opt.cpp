#include<bits/stdc++.h>
#define ll long long
#define db double
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,mod=998244353;
int n,m;
int a[maxn];
char s[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
vector<int> v[10];
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
        v[s[i]-'0'].eb(i);
    for(int i=0;i<10;i++){
        auto it=lower_bound(v[i].begin(),v[i].end(),a[m]);
        if(it==v[i].end())  continue;
        while(it!=v[i].end()){
            a[++m]=*it;it++;
        }
    }
    int ans=0,inv10=qpow(10,mod-2);
    for(int i=1;i<=m;i++)
        madd(ans,immul(qpow(inv10,i),'9'-s[a[i]]));
    printf("%d\n",ans);
}