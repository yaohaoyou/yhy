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
const char digits[] = "0123456789ABCDEF";
int x;ll n;
ll ans;
bool decToBase(ll num, int base) {
    string result="";
    while(num>0) {result+=digits[num%base];num/=base;}
    for(int i=0,j=result.length()-1;i<j;i++,j--)
        if(result[i]^result[j]) return false;
    return true;
}
int rev(int x){
    vector<int> v;
    while(x)    v.eb(x%10),x/=10;
    int r=0;
    for(int i:v)    r=r*10+i;
    return r;
}
int main(){
    ll ans=0;
    scanf("%d%lld",&x,&n);
    vector<int> v;
    ll t=n,w=0;
    while(t)    v.eb(t%10),t/=10;
    // printf("%d\n",v.size());
    for(int i=v.size()-1;i>=max(0,(int)v.size()/2-1);i--)    w=w*10+v[i];
    // debug("w = %d\n",w);
    for(int i=1,j=10;i<=w;i++){
        if(i==10)   j=100;
        if(i==100)  j=1000;
        if(i==1000)  j=10000;
        if(i==10000)  j=100000;
        if(i==100000)  j=1000000;
        if(i==1000000)  j=10000000;
        if(i==10000000)  j=100000000;
        if(i==100000000)  j=1000000000;
        int ri=rev(i/10);
        ll m=1ll*j*i+ri+(i%10)*j/10;
        // debug("m = %d\n",m);
        if(m<=n&&decToBase(m,x))    ans+=m;
        m=1ll*(j/10)*i+ri;
        // debug("# m = %d\n",m);
        if(m<=n&&decToBase(m,x))    ans+=m;
    }
    printf("%lld\n",ans);
}