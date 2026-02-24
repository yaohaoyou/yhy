// P4195 【模板】扩展 BSGS/exBSGS
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
int mod;
unordered_map<int,int> mp;
namespace MyMod{
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
void exgcd(int a,int b,int &x,int &y){
    if(!b)  return x=1,y=0,void();
    exgcd(b,a%b,y,x);y-=a/b*x;
}
inline int bsgs(int a,int b){
    mp.clear();
    a%=mod;b%=mod;
    int B=ceil(sqrt(mod)),p=b;
    for(int i=1;i<=B;i++)   mmul(p,a),mp[p]=i;
    int q=1,k=1;
    for(int i=1;i<=B;i++)   mmul(q,a);
    for(int i=1;i<=B;i++){
        mmul(k,q);
        if(mp.find(k)!=mp.end())    return i*B-mp[k];
    }
    return -1;
}
inline int inv(int x){return exgcd(x,mod,x,*new int),(x%mod+mod)%mod;}
inline int exbsgs(int a,int b){
    a%=mod;b%=mod;
    int cnt=0,d=__gcd(a,mod);
    while(d^1){
        if(b==1)    return cnt;
        if(b%d) return -1;
        mod/=d;b=immul(b/d,inv(a/d));
        d=__gcd(a%=mod,mod);cnt++;
    }
    int ans=bsgs(a,b);
    return ~ans?ans+cnt:-1;
}
int main(){
    int a,b;
    scanf("%d%d%d",&a,&mod,&b);
    while(a){
        int ans=exbsgs(a,b);
        if(~ans)    printf("%d\n",ans);
        else    puts("No Solution");
        scanf("%d%d%d",&a,&mod,&b);
    }
}