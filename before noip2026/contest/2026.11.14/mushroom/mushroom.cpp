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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e6+10;
int n,m,tot;
int a[maxn],b[maxn],c[maxn];
int f[maxn][2];
int nx[maxn][3];
void dfs(int u,int x){
    mems(f[u],0x3f);
    if(u<=n){
        if(a[u])    f[u][a[u]>=x]=0;
        else    f[u][0]=0,f[u][1]=1;
        return;
    }
    for(int i=0;i<3;i++)    dfs(nx[u][i],x);
    for(int i=0;i<8;i++){
        ll w=0;
        for(int j=0;j<3;j++)w+=f[nx[u][j]][(i>>j)&1];
        if(__builtin_popcount(i)>=2)    gmn(f[u][1],w);
        else    gmn(f[u][0],w);
    }
}
bool check(int x){
    int cnt[2]={0,0};
    for(int i=1;i<=m;i++)cnt[c[i]>=x]++;
    dfs(tot,x);
    return f[tot][1]<=cnt[1];
}
bool mem2;
int main(){
    freopen("mushroom.in","r",stdin);freopen("mushroom.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int x,y;scanf("%d%d",&x,&y);a[y]=x;b[i]=x;}
    for(int i=m+1;i<=n;i++) scanf("%d",&b[i]),c[i-m]=b[i];
    queue<int> q;
    for(int i=1;i<=n;i++)   q.ep(i);
    tot=n;
    while(q.size()^1){
        int x=q.front(),y,z;q.pop();y=q.front();q.pop();z=q.front();q.pop();
        tot++;
        nx[tot][0]=x;nx[tot][1]=y;nx[tot][2]=z;
        q.ep(tot);
    }
    m=n-m;
    sort(b+1,b+n+1);int k=unique(b+1,b+n+1)-b-1;
    int l=1,r=k,ans;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(b[mid]))   ans=b[mid],l=mid+1;
        else    r=mid-1;
    }
    printf("%d\n",ans);
}