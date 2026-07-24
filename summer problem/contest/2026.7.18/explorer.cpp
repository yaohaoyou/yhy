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
int n;
int a[maxn],pr[maxn],nx[maxn],buc[maxn],s[maxn];
int w[maxn];
struct BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n+n){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n+n;i++)tr[i]=0;}
}T;
vector<pii> I[maxn],E[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1,x,y;i<=n;i++){scanf("%d%d",&x,&y);a[x]=a[y]=i;}
    n<<=1;
    for(int i=1;i<=n;i++)   a[i+n]=a[i];
    for(int i=1;i<=n+n;i++) debug("%d ",a[i]);debug("\n");
    for(int i=n+n;i;i--){
        nx[i]=buc[a[i]];
        buc[a[i]]=i;
    }
    for(int i=1;i<=n+n;i++) pr[nx[i]]=i;
    for(int i=1;i<=n;i++)if(nx[i]<=n)s[i]++;
    for(int i=n;i;i--)  s[i]+=s[i+1];
    ll ans=0;
    for(int i=1;i<=n;i++){
        int x=nx[i],r=i+n-1;
        for(int j=x+1;j<=r;j++)if(nx[j]<=r)ans+=s[nx[j]];
        for(int j=1;j<=pr[i+n];j++) s[j]++;
    }
    assert(ans%3==0);
    for(int i=1;i<=n;i++){
        int x=nx[i];if(x>n) continue;
        for(int j=i+1;j<x;j++)if(nx[j]>x&&nx[j]<=n){
            // printf("[%d,%d)\n",j,x);
            T.add(j,1),T.add(x,-1);
            E[i].eb(j,x);
        }
    }
    for(int i=1;i<=n;i++){
        int x=nx[i],r=i+n-1;
        for(auto [j,k]:I[i])    T.add(j,1),T.add(k,-1);
        for(auto [j,k]:E[i])    T.add(j,-1),T.add(k,1);
        // if(T.que(x))    printf("add %d %d %d\n",i,x,T.que(x));
        ans+=T.que(x);
        for(int j=x+1;j<=r;j++)if(nx[j]>i+n&&nx[j]<=x+n){
            // printf("%d %d : [%d,%d)\n",a[i],a[j],j,i+n);
            // T.add(j,1),T.add(i+n,-1);
            I[nx[j]-n+1].eb(j,i+n);
            E[x].eb(j,i+n);
        }
    }
    ans/=3;
    printf("%lld\n",ans);
}