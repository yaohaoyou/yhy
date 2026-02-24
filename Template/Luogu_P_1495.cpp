//  P1495 【模板】中国剩余定理（CRT）/ 曹冲养猪
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=110;
int n;
ll m;
ll sum=1;
int a[maxn],b[maxn];
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1;y=0;
        return a;
    }
    int gcd=exgcd(b,a%b,x,y);
    int xx=x;
    x=y;
    y=xx-a/b*y;
    return gcd;
}
inline ll lcm(ll x,ll y){return x/__gcd(x,y)*y;}
ll ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i],&b[i]);
        sum=lcm(sum,a[i]);
    }
    for(int i=1;i<=n;i++){
        m=sum/a[i];
        ll x,y;
        exgcd(m,a[i],x,y);
        if(x<0) x+=a[i];
        (ans+=__int128(b[i])*m%sum*x%sum)%=sum;
    }
    printf("%lld\n",ans);
}