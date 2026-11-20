#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
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
const int maxn=1.5e5+10,bs=6041989;
int n;
char s[maxn];
int nx[maxn][30],a[maxn],sa[maxn];
ull spq[maxn],pq[maxn],H[maxn];
inline ull hsh(int l,int r){
    ull res=H[r]-H[l-1]*pq[r-l+1]-spq[r-l]*l;
    for(int i=0;i<26;i++)if(nx[l][i]<=r){
        int x=nx[l][i];
        res+=(l-a[x])*pq[r-x];
    }
    return res;
}
inline int lcp(int x,int y){
    int l=1,r=min(n-x+1,n-y+1),p=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(hsh(x,x+mid-1)==hsh(y,y+mid-1))  p=mid,l=mid+1;
        else    r=mid-1;
    }
    if(x+p<=n&&y+p<=n)assert(a[x+p]^a[y+p]);
    return p;
}
inline bool cmp(int x,int y){
    int p=lcp(x,y);
    if(x+p>n||y+p>n)return x+p>n;
    int ax=a[x+p]-10>=x?a[x+p]-x:0,ay=a[y+p]-10>=y?a[y+p]-y:0;
    return ax<ay;
}
bool mem2;
int main(){
    // freopen("meowcipher.in","r",stdin);freopen("meowcipher.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%s",&n,s+1);
    mems(nx[n+1],0x3f);
    for(int i=n;i;i--){
        memc(nx[i],nx[i+1]);
        if(nx[i][s[i]-'a']<=n)a[nx[i][s[i]-'a']]=i+10;
        nx[i][s[i]-'a']=i;
    }
    for(int i=1;i<=n;i++)H[i]=H[i-1]*bs+a[i];
    spq[0]=pq[0]=1;for(int i=1;i<=n;i++)pq[i]=pq[i-1]*bs;
    for(int i=1;i<=n;i++)spq[i]=spq[i-1]+pq[i];
    iota(sa+1,sa+n+1,1);
    stable_sort(sa+1,sa+n+1,cmp);
    ll ans=0;
    for(int i=1;i<=n;i++)   ans+=n-i+1;
    for(int i=2;i<=n;i++)   ans-=lcp(sa[i-1],sa[i]);
    printf("%lld\n",ans);
}