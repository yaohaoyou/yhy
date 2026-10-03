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
const int maxn=2e5+10;
bool mem1;
int n,m;
// ll a[maxn];
// int sg[maxn];
bool mem2;
void matt(int _cases){
    scanf("%d%d",&n,&m);
    const ll N=(1ll<<m+1)-1;
    ll al=0;
    for(int i=1;i<=n;i++){
        ll x;scanf("%lld",&x);
        al^=(x%N);
    }
    puts(al?"First":"Second");
    // sg[0]=0;
    // for(int i=1;i<=n;i++){
    //     set<int> st;
    //     for(int j=1;j<=i;j++)if(__builtin_popcount(j)<=m)st.ep(sg[i-j]);
    //     sg[i]=0;
    //     while(st.count(sg[i]))sg[i]++;
    // }
    // for(int i=0;i<=n;i++){
    //     printf("%d ",sg[i]);
    //     if((i+1)%63==0) puts("");
    // }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}