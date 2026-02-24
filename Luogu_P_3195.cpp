#include<bits/stdc++.h>
#define ll long long
#define db double
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e4+10;
int n,l;
int a[maxn];
ll s[maxn];
db dp[maxn];
inline db sqr(db x){return 1.0*x*x;}
inline db X(int x){return s[x]+x;}
inline db Y(int x){return dp[x]+sqr(s[x]+x);}
inline db slope(int x,int y){return 1.0*(Y(x)-Y(y))/(X(x)-X(y));}
int q[maxn],hd=1,en;
int main(){
    scanf("%d%d",&n,&l);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);s[i]=s[i-1]+a[i];}
    q[++en]=0;
    for(int i=1;i<=n;i++){
        ll u=s[i]+i-l-1;
        while(en-hd>=1&&slope(q[hd],q[hd+1])<=2*u)    hd++;
        int j=q[hd];
        dp[i]=dp[j]+sqr(u-X(j));
        while(en-hd>=1&&slope(q[en-1],q[en])>=slope(q[en-1],i))    en--;
        q[++en]=i;
    }
    printf("%lld\n",(ll)dp[n]);
}