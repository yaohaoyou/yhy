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
int a,b;ll n;
void exgcd(int a,int b,int &x,int &y){
    if(!b)  return x=1,y=0,void();
    exgcd(b,a%b,x,y);
    int t=x;
    x=y;y=t-(a/b)*y;
}
void matt(int _cases){
    scanf("%d%d%lld",&a,&b,&n);
    if(b==1)    return puts(n<=a?"Yes":"No"),void();
    int x,y,nn=(n-1)%b+1;
    exgcd(b,a,x,y);
    x=(1ll*-x*nn%a+a)%a;
    puts(nn+1ll*b*x>=n?"Yes":"No");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
// nn+bx=ay
// bx-ay=nn
// ay=bx-nn