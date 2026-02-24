//  SP288 PON - Prime or Not
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int pri[12]={2,3,5,7,11,13,17,37,61,24251};
int n;
int mod;
int mul(int x,int y){
    int res=0;
    while(y){
        if(y&1) res=(res+x)%mod;
        x=(x+x)%mod;
        y>>=1;
    }
    return res;
}
inline int qpow(int x,int y){
    x%=mod;
    int res=1;
    while(y){
        if(y&1)	res=mul(res,x)%mod;
        x=mul(x,x)%mod;
        y>>=1;
    }
    return res;
}
bool Miller_Rabin(int a){
    int d=n-1,r=0;
    while(!(d&1)){d>>=1;r++;}
    mod=n;
    int k=qpow(a,d);
    // printf("%d %d %d %d\n",a,d,r,k);
    if(k==1)    return true;
    for(int i=0;i<r;i++){
        // printf("%d %d\n",k,n);
        if(k==(n-1))  return true;
        k=mul(k,k);
    }
    return false;
}
void solve(){
    scanf("%lld",&n);
    for(int i=0;i<9;i++){
        if(n==pri[i])   return puts("YES"),void();
        if(n%pri[i]==0) return puts("NO"),void();
        if(!Miller_Rabin(pri[i]))   return puts("NO"),void();
    }
    puts("YES");
}
signed main(){
    // n=5;
    // printf("%d\n",Miller_Rabin(3));
    int t;
    scanf("%lld",&t);
    while(t--)  solve();
}