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
const int maxn=4e5+10;
int n,m;
int a[maxn],b[maxn];
bool vis[maxn];
struct Linear_basis{
    int siz;
    int p[20],v[20];
    void ins(int x){
        int X=x;
        for(int i=18;~i;i--){
            if(!(x&(1<<i))) continue;
            if(!p[i])   return p[i]=x,v[i]=X,siz++,void();
            x^=p[i];
        }
    }
    bool query(int x){
        for(int i=18;~i;i--){
            if(!(x&(1<<i)))   continue;
            x^=p[i];
            if(!x)  return true;
        }
        return false;
    }
    void dfs(int d){
        if(!~d) return;
        dfs(d-1);
        b[++m]=v[d];
        dfs(d-1);
    }
}L;
int main(){
    scanf("%d",&n);
    int ans=0;
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);vis[a[i]]=true;}
    for(int i=1;i<=18;i++){
        for(int j=1<<i-1;j<1<<i;j++)
            if(vis[j])  L.ins(j);
        if(L.siz==i)    ans=i;
    }
    L.dfs(ans);
    printf("%d\n0 ",ans);
    int lst=0;
    for(int i=1;i<1<<ans;i++)   printf("%d ",b[i]^=b[i-1]);
}