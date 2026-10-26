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
int n;
int a[maxn],b[maxn];
bitset<maxn> dp;
// inline void ask(int x){a[x]=b[x];}
inline void ask(int x){if(~a[x])return;printf("? %d\n",x);fflush(stdout);char y[5];scanf("%s",y);a[x]=y[0]=='Y';}
inline void out(int x){printf("! %d\n",x);fflush(stdout);}
void data(){
    n=rand()%100+1;
    printf("%d\n",n);
    mems(b,0);
    for(int i=1;i<=n/2;i++)b[i]=1;
    random_shuffle(b+1,b+n+1);
    for(int i=1;i<=n;i++)if(b[i])printf("%d ",i);puts("");fflush(stdout);
}
bool mem2;
void matt(int _cases){
    // data();
    scanf("%d",&n);
    fill(a,a+n+1,-1);
    int m=n>>1;
    if(!(n&1)){
        ask(m);if(!a[m])return out(2);
        m--;
    }
    for(int i=1;i<=m;i++)  ask(i);
    int s[2]={0,0};
    for(int i=1;i<=m;i++)s[a[i]]++;
    bool o=s[0]>s[1];
    for(int i=1;i<=m;i++)if(a[i]==o){
        ask(n-i);
        if(a[n-i]==o)   return out(2);
    }
    vector<int> S;
    if(o){
        for(int i=1;i<=m;i++)if(!a[i])a[n-i]=1;
    }
    for(int i=1;i<=n;i++)if(a[i]==1)S.eb(i);
    // for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");
    assert(S.size()==n/2);
    dp.reset();dp.set(0);
    for(int i:S){
        dp|=dp<<i;
        if(dp[n])   return out(3);
    }
    out(-1);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}