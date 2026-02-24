#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10,B=100;
int n,ans;
int a[maxn];
set<int> fac;
mt19937 rnd(time(0) * (unsigned long long)(new char));
void Make_Factors(int x){
    if(x<=1)    return;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            while(x%i==0)   x/=i;
            fac.insert(i);
        }
    }
    if(x!=1)   fac.insert(x);
}
inline int random(int l,int r){return rnd()%(r-l+1)+l;}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        ans+=(a[i]&1);
    }
    for(int i=1;i<=B;i++){
        int x=a[random(1,n)];
        Make_Factors(x-1);Make_Factors(x);Make_Factors(x+1);
    }
    for(int x:fac){
        int now=0;
        for(int i=1;i<=n;i++){
            int c=min(a[i]%x,x-a[i]%x);
            if(a[i]<x)  c=x-a[i];
            now+=c;
        }
        ans=min(ans,now);
    }
    printf("%lld\n",ans);
}