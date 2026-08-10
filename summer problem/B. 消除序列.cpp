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
const ll INF=1e18;
int n;
int a[maxn],b[maxn];ll s[2][maxn];
unordered_map<ll,int> mp[2];
int cnt;
vector<int> v[maxn];
struct ST{
    ll st[20][maxn];int Log[maxn];
    void build(bool o){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=0;i<=n;i++)   st[0][i]=INF;
        for(int i=o?1:2;i<=n;i+=2)  st[0][i]=s[o][i];
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline ll query(int l,int r){int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
    inline void clear(){for(int j=0;j<20;j++)for(int i=0;i<=n;i++)st[j][i]=INF;}
}st[2];
inline int calc(int x,ll s0,ll s1){
    int l=x,r=n,p=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(st[0].query(x,mid)>=s0&&st[1].query(x,mid)>=s1)  p=mid,l=mid+1;
        else    r=mid-1;
    }
    return p;
}
void matt(){
    mp[0].clear();mp[1].clear();for(int i=1;i<=cnt;i++)v[i].clear();cnt=0;
    for(int i=1;i<=n;i++)a[i]=b[i]=0;st[0].clear();st[1].clear();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   b[i]=a[i]-a[i-1];
    s[1][1]=b[1];
    for(int i=2;i<=n;i++)   s[i&1][i]=s[i&1][i-2]+b[i];
    // for(int i=2;i<=n;i+=2)  printf("%d ",s[0][i]);puts("");
    // for(int i=1;i<=n;i+=2)  printf("%d ",s[1][i]);puts("");
    st[0].build(0);st[1].build(1);
    for(int i=1;i<=n;i++){
        int &t=mp[i&1][s[i&1][i]];
        if(!t)  t=++cnt;
        v[t].eb(i);
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        bool o=i&1;
        //! s[i&1][j]-s[i&1][i-2]+a[i-1]==0;
        // ans+=mp[i&1][(i==1?0:s[i&1][i-2])-a[i-1]];
        // ans+=(!a[i]);
        int c0=a[i],c1=0;
        // for(int j=i+2;j<=n;j+=2){
        //     c0+=b[j];c1+=b[j-1];
        //     if(c0<0||c1<0)  break;
        //     ans+=c0==0;
        // }
        int rj;
        if(!o)  rj=calc(i,s[o][i]-a[i],s[!o][i-1]);
        else    rj=calc(i,s[!o][i-1],s[o][i]-a[i]);
        // printf("[%d,%d]\n",i,rj);
        if(rj>=i&&mp[o].find(s[o][i]-a[i])!=mp[o].end()){
            int id=mp[o][s[o][i]-a[i]];
            ans+=upper_bound(v[id].begin(),v[id].end(),rj)-lower_bound(v[id].begin(),v[id].end(),i);
            // printf("i = %d\n",i);
            // for(int j:v[id])printf("%d ",j);printf("\n%d\n",upper_bound(v[id].begin(),v[id].end(),rj)-lower_bound(v[id].begin(),v[id].end(),i));
        }
        // c0=c1=0;
        // b[i]=a[i];
        // for(int j=i+1;j<=n;j+=2){
        //     c0+=b[j];c1+=b[j-1];
        //     if(c0<0||c1<0)  break;
        //     ans+=c0==0;
        // }
        // b[i]=a[i]-a[i-1];
        //! s[!o][j]-s[!o][i-1]==0 s[o][j-1]-s[o][i]+a[i]>=0
        if(!o)  rj=calc(i+1,s[o][i]-a[i],s[!o][i-1]);
        else    rj=calc(i+1,s[!o][i-1],s[o][i]-a[i]);
        // printf("[%d,%d]\n",i,rj);
        if(rj>=i+1&&mp[!o].find(s[!o][i-1])!=mp[!o].end()){
            int id=mp[!o][s[!o][i-1]];
            ans+=upper_bound(v[id].begin(),v[id].end(),rj)-lower_bound(v[id].begin(),v[id].end(),i+1);
            // printf("i = %d\n",i);
            // for(int j:v[id])printf("%d ",j);printf("\n%d\n",upper_bound(v[id].begin(),v[id].end(),rj)-lower_bound(v[id].begin(),v[id].end(),i));
        }
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}