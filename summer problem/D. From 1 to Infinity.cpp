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
ll calc(ll n){
    if(!n)    return 0;
    ll s=0,bs=1;
    while(bs<=n){
        ll x=n/(bs*10),y=n%(bs*10),now=y/bs;
        s+=x*bs*45;
        for(int d=1;d<now;d++)  s+=d*bs;
        s+=now*(y%bs+1);
        bs*=10;
    }
    return s;
}
ll n;
void matt(){
    scanf("%lld",&n);
    ll d=1,bs=1;
    while(n>d*9*bs){n-=d*9*bs;d++;bs*=10;}
    ll x=bs+(n-1)/d;
    string s=to_string(x);
    ll p=(n-1)%d+1,sum=0;
    for(int i=0;i<p;i++)   sum+=s[i]-'0';
    printf("%lld\n",calc(x-1)+sum);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}