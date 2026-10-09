#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e6+10;
int n;
int a[maxn];
priority_queue<pii,vector<pii>,greater<pii>> q;
int pr[maxn],nx[maxn],out[maxn];
bool vis[maxn];
char s[maxn];
inline void era(int x){int pre=pr[x],nxt=nx[x];nx[pre]=nxt;pr[nxt]=pre;}
bool mem2;
void matt(int _cases){
    while(!q.empty())q.pop();
    fill(vis,vis+n+1,0);fill(out,out+n+1,0);
    scanf("%d%s",&n,s+1);
    for(int i=1;i<n;i++)    a[i]=(s[i]!='R')+(s[i+1]!='S');
    for(int i=1;i<n;i++)    q.ep(a[i],i),nx[i]=i+1,pr[i]=i-1;pr[0]=nx[n]=0;
    a[0]=a[n]=1e9;
    ll ans=0;
    int m=0;
    while(m<n/2){
        int x=q.top().se;q.pop();
        if(vis[x])  continue;
        ans+=a[x];
        a[x]=a[pr[x]]+a[nx[x]]-a[x];q.ep(a[x],x);
        vis[pr[x]]=vis[nx[x]]=true;
        if(pr[x])era(pr[x]);
        if(nx[x]<n)era(nx[x]);
        m++;
        out[ans]=m;
    }
    for(int i=1;i<=n;i++)   gmx(out[i],out[i-1]);
    for(int i=0;i<=n;i++)   printf("%d ",out[i]);puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}