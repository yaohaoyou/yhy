#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
using namespace __gnu_pbds;
const int maxn=2e5+10;
int n;
int a[maxn],mu[maxn],phi[maxn];
bool ntpri[maxn];
vector<int> d[maxn],p;
// template <> struct tr1::hash<pii>{
//     size_t operator()(pii x)const{return ((ull)x.fi<<32)^x.se;}
// };
// cc_hash_table<pii,int> f;
cc_hash_table<int,int> f[maxn];
void seive(){
    const int N=2e5;
    phi[1]=1;mu[1]=1;
    for(int i=2;i<=N;i++){
        if(!ntpri[i])   p.eb(i),mu[i]=-1,phi[i]=i-1;
        for(int j:p){
            if(1ll*i*j>N)   break;
            ntpri[i*j]=true;
            if(i%j==0){mu[i*j]=0,phi[i*j]=phi[i]*j;break;}
            else mu[i*j]=-mu[i],phi[i*j]=phi[i]*phi[j];
        }
    }
    for(int i=1;i<=N;i++)if(mu[i])for(int j=i;j<=N;j+=i)d[j].eb(i);
}
void data(){
    srand(time(0));
    n=2e5;
    iota(a+1,a+n+1,1);
    random_shuffle(a+1,a+n+1);
    printf("%d\n",n);
    for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");
    exit(0);
}
int main(){
    // data();
    scanf("%d",&n);
    seive();
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    ll ans=1ll*n*(n+1)/2;
    for(int i=1;i<=n;i++)   ans-=phi[i]<<1;
    for(int i=1;i<=n;i++)for(int x:d[i])for(int y:d[a[i]])f[x][y]++;
    for(int i=1;i<=n;i++)for(pii x:f[i])ans+=1ll*mu[i]*mu[x.fi]*x.se*(x.se+1)/2;
    printf("%lld\n",ans);
}