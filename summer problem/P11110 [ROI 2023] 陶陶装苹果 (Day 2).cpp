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
const int maxn=3e5+10;
int n,q;
ll a[maxn],s[maxn],h[maxn];
bool f[maxn];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    bool flag=true;int en=n+1;
    h[0]=LLONG_MAX;
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i];
    for(int i=1;i<=n;i++){
        if(flag&&2*(a[i]-1)<=s[i-1]){
            h[i]=h[i-1];f[i]=true;
        }
        else if(a[i]-1<=s[i-1]) flag=false,h[i]=min(h[i-1],s[i-1]-a[i]+1);
        else{en=i-1;break;}
    }
    int z;ll v=0;scanf("%d",&z);
    for(int i=1;i<=q;i++){
        ll k,a,b;scanf("%lld%lld%lld",&k,&a,&b);
        k-=v*z;a-=v*z;b-=v*z;
        if(!a&&!b){puts("Yes");v+=i;continue;}
        if(k<::a[1]){puts("No");continue;}
        k=upper_bound(::a+1,::a+n+1,k)-::a-1;
        if(k>en)k=en;
        if(a+b>s[k]){puts("No");continue;}
        if(a<b) swap(a,b);
        if(f[k]){puts("Yes");v+=i;continue;}
        k=lower_bound(s+1,s+n+1,a+b)-s;
        if(f[k]||a>=s[k]-h[k])    puts("Yes"),v+=i;
        else{
            if(b<=h[k]) puts("Yes"),v+=i;
            else    puts("No");
        }
    }
}