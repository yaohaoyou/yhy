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
bool mem1;
const int maxn=1e5+10;
int n,k;
ll ans;
int a[maxn],h[maxn];
set<pii> s;
struct st{
    int Log[maxn];
    pii st[20][maxn];
    void build(){
        for(int i=2;i<=n;i++)Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)st[0][i]=pii(h[i],i);
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    pii query(int l,int r){if(l>r)return pii(0,0);int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
bool mem2;
void dvd(int l,int r,int s){
    if(l>r)return;
    int p=st.query(l,r).se;
    ans+=h[p]-s;
    dvd(l,p-1,h[p]);dvd(p+1,r,h[p]);
}
int main(){
    freopen("roadblock.in","r",stdin);freopen("roadblock.out","w",stdout);
    debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&h[i]);
    st.build();
    for(int i=n+1;i;i--)    a[i]-=a[i-1];
    for(int i=1;i<=n+1;i++)   s.ep(a[i],i);
    for(int i=1;i<=n+1;i++){
        while(a[i]<-k){
            s.erase(pii(a[i],i));
            int x=prev(s.end())->se;
            // assert(a[x]>=-k);
            if(a[x]<=k){ans+=-k-a[i];break;}
            s.erase(pii(a[x],x));
            int d=min(-k-a[i],a[x]-k);//assert(d>0);
            // printf("+ %d %d %d : ",a[i],a[x],d);
            a[i]+=d;a[x]-=d;ans+=d;//assert(a[x]>=-k);
            // printf("%d %d\n",a[i],a[x]);
            s.ep(a[i],i);s.ep(a[x],x);
        }
        while(a[i]>k){
            s.erase(pii(a[i],i));
            int x=s.begin()->se;
            // assert(a[x]<=k);
            if(a[x]>=-k){ans+=a[i]-k;break;}
            s.erase(pii(a[x],x));
            int d=min(a[i]-k,-k-a[x]);//assert(d>0);
            // printf("- %d %d %d : ",a[i],a[x],d);
            a[i]-=d;a[x]+=d;ans+=d;//assert(a[x]<=k);
            // printf("%d %d\n",a[i],a[x]);
            s.ep(a[i],i);s.ep(a[x],x);
        }
    }
    dvd(1,n,0);
    printf("%lld\n",ans);
}