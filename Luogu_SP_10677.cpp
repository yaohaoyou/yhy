#define __opt optimize
#pragma GCC __opt(2,3,"Ofast")
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e9+10;
int n,k;
ll ans;
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i+=2){ans+=k%i;ans+=(k+1)%i;}
    if(n&1)ans-=k%(n+1);
    printf("%lld\n",ans);
}