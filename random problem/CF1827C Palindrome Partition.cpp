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
const int maxn=1e6+10,lgV=20;
int n;
char s[maxn],t[maxn];
int q[maxn],p[maxn];
void manacher(){
    int cnt=0;
    t[++cnt]='!';
    for(int i=1;i<=n;i++)   t[++cnt]='|',t[++cnt]=s[i];
    t[++cnt]='@';
    for(int i=1,r=0,mid=0;i<=cnt;i++){
        q[i]=i>r?1:min(q[(mid<<1)-i],r-i+1);    
        while(t[i+q[i]]==t[i-q[i]]) q[i]++;
        if(i+q[i]>r){r=i+q[i]-1;mid=i;}
    }
    for(int i=4,j=1;i<cnt;i+=2,j++) p[j]=q[i]>>1;
}
struct DSU{
    int fa[maxn],siz[maxn];
    inline void init(){for(int i=0;i<=n+n;i++)fa[i]=i,siz[i]=(i<=n);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){if((x=find(x))==(y=find(y)))return;fa[y]=x;siz[x]+=siz[y];}
}U[lgV+1];
int _;
void matt(){
    scanf("%d%s",&n,s+1);
    manacher();
    for(int i=0;i<=lgV;i++) U[i].init();
    for(int i=1;i<n;i++){
        if(!p[i])   continue;
        int l1=i-p[i],r1=i,l2=i,r2=i+p[i];
        {int l=l2,r=r2;l2=2*n-r;r2=2*n-l;}
        for(int j=lgV;~j;j--)
            if((r1-l1+1)>=(1<<j)){U[j].merge(l1,l2);l1+=(1<<j);l2+=(1<<j);}
    }
    for(int i=lgV;i;i--){
        for(int j=0;j+(1<<i)-1<=n+n;j++){
            int f=U[i].find(j);
            if(f^j) U[i-1].merge(f,j),U[i-1].merge(f+(1<<i>>1),j+(1<<i>>1));
        }
    }
    for(int i=0;i<=n;i++)   U[0].merge(i,n+n-i);
    auto C2=[&](int x){return 1ll*x*(x-1)/2;};
    ll ans=0;
    for(int i=0;i<=n+n;i++)
        if(U[0].find(i)==i) ans+=C2(U[0].siz[i]);
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(_=1;_<=T;_++)matt();}