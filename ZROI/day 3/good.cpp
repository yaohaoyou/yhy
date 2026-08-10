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
const int maxn=2e6+10;
int n,m;
int s1,s2,lim;
int a[maxn];
ll sum[maxn];
bool ans[maxn];
void dfs(int x,int s,int num){
    // if(num&&!s){
    //     printf("%d %d\n",x-num,x-1);
    //     for(int i=x-num;i<=x-1;i++) printf("%d",ans[i]);
    //     assert(s1==s2);
    //     exit(0);
    // }
    if(num==m||x>n) return;
    ans[x]=0;s1+=a[x];if(s1<=lim)dfs(x+1,s+a[x],num+1);s1-=a[x];
    ans[x]=1;s2+=a[x];if(s2<=lim)dfs(x+1,s-a[x],num+1);s2-=a[x];
}
mt19937 matt(time(0));
inline int rnd(){return abs(int(matt()));}
int main(){
    // freopen("good.in","r",stdin);freopen("good.out","w",stdout);
    scanf("%d",&n);n<<=1;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int x=1;
    for(int i=1;i<=n;i++){
        a[i]=x;
        x<<=1;
        if(x>n/2) x=1;
    }
    // for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");return 0;
    // for(int i=1;i<=n;i++)   a[i]=rnd()%1000000+1;
    for(int i=1;i<=n;i++)   sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++){
        if(!a[i])   return printf("%d %d\n0\n",i,i),0;
        if(a[i]==a[i-1])    return printf("%d %d\n01\n",i-1,i),0;
    }
    m=min(n,40);
    while(1){
        debug("guess\n");
        int s=rnd()%n+1;lim=(sum[min(s+m-1,n)]-sum[s-1]+1)/2;
        debug("a[%d] = %d\n",s,a[s]);
        dfs(s,0,0);
    }
    // for(int i=1;i<=30;i++)  printf("%d ",a[i]);puts("");
    puts("-1");
}