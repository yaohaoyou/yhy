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
ll n;
inline ll Pow(int x,int y){ll res=1;while(y--)res*=x;return res;}
vector<ll> v;
int main(){
    scanf("%lld",&n);
    int x=log10(n)/log10(2),y=log10(n)/log10(5);
    ll ans=0;
    for(int i=0;i<=x;i++)for(int j=0;j<=y;j++){if(Pow(2,i)*Pow(5,j)>n)break;v.eb(Pow(2,i)*Pow(5,j));}
    sort(v.begin(),v.end());
    int c=v.size()-1;
    for(ll l=1,r;l<=n;l=r+1){
        r=min(n,n/(n/l));
        while(c>=0&&v[c]>n/l)    c--;
        ans+=(n/l)*(r-l+1)*(c+1);
    }
    c=v.size()-1;
    for(ll l=1,r;l<=n;l=r+1){
        if(l&1){l++;if(l>n)break;}
        r=min(n,n/(n/l));
        if(r&1) r--;
        while(c>=0&&v[c]>n/l)    c--;
        if(l<=r)    ans-=(c+1)*(n/l)*(r/2-l/2+1),ans+=(c+1)*(n/l)*(r/10-(l+9)/10+1);
    }
    c=v.size()-1;
    for(ll l=1,r;l<=n;l=r+1){
        l=(l+4)/5*5;if(l>n)break;
        r=min(n,n/(n/l));
        r=r/5*5;
        while(c>=0&&v[c]>n/l)    c--;
        if(l<=r)    ans-=(c+1)*(n/l)*(r/5-l/5+1);
    }
    printf("%lld\n",ans);
}