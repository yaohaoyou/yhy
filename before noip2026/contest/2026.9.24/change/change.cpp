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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e5+10;
bool mem1;
int n;
int a[maxn];
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    ll ans=a[1];
    int g=0;
    for(int i=2;i<=n;i++)   g=__gcd(g,abs(a[i]-a[i-1]));
    g<<=1;
    if(a[1]>=g){
        if(a[1]%g)  ans%=g;
        else    ans=g;
    }
    for(int i=2;i<=n;i++)   ans+=abs(a[i]-a[i-1]);
    // printf("g = %d\n",g);
    printf("%lld\n",ans);
    // int A=a[1],B=a[2];
    // if(A>B) B=A+A-B;
    // int x=A,y=B;
    // while(x>0){
    //     if(x+A+A-B-B>0) x+=A+A-B-B;
    //     else break;
    // }
    // // printf("%d ",x);
    // // printf("%d %d ",A,B);
    // if(A+A-B<x)    return printf("%d\n",B),void();
    // y=A+A-B;
    // while(y>0){
    //     if(y+A+A-B-B>=x)    y+=A+A-B-B;
    //     else break;
    // }
    // printf("%d\n",y);
}
int main(){freopen("change.in","r",stdin);freopen("change.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}