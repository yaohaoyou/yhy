// P3846 [TJOI2007] 可爱的质数/【模板】BSGS
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
int a,b,mod;
unordered_map<int,int> mp;
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace MyMod;
inline int bsgs(){
    int B=ceil(sqrt(mod));
    int p=b;
    for(int i=1;i<=B;i++)   mmul(p,a),mp[p]=i;
    int q=qpow(a,B),k=1;
    for(int i=1;i<=B;i++){
        mmul(k,q);
        if(mp.find(k)!=mp.end()) return i*B-mp[k];
    }
    return -1;
}
int main(){
    scanf("%d%d%d",&mod,&a,&b);
    a%=mod;b%=mod;
    int ans=bsgs();
    if(~ans)    printf("%d\n",ans);
    else    puts("no solution");
}