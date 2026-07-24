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
const int maxn=2.5e5+10,V=1e9,inf=1e9;
const ll INF=1e18;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
bool mem1;
int n,m;
ll ans;
struct node{int x,y,c;}a[maxn];
map<int,ll> s;
int b[maxn<<1];
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,V
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    const int maxm=maxn*40;
    int tot;
    ll sum[maxm],mx[maxm];
    int lc[maxm],rc[maxm];
    inline void pu(int p){sum[p]=sum[ls]+sum[rs];mx[p]=max(mx[ls],mx[rs]-sum[ls]);}
    void upd(setpos,int x,int s){if(!p)p=++tot;if(l==r)return sum[p]=s,mx[p]=x-s,void();setmid;(x<=mid)?upd(lson,x,s):upd(rson,x,s);pu(p);}
}
using namespace SegmentTree;
bool mem2;
void maker(){
    srand(time(0));
    n=20;
    printf("%d\n",n);
    for(int i=1;i<=n;i++)   printf("%d %d %d\n",rand()%10,rand()%10,rand()%2?rand()%10:-rand()%10);
    exit(0);
}
void baoli(){
    for(int i=1;i<=n;i++)   b[++m]=a[i].x,b[++m]=a[i].y;
    sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;
    for(int i=1;i<=m;i++){
        for(int j=i;j<=m;j++){
            ll res=-(b[j]-b[i]);
            for(int k=1;k<=n;k++)if(a[k].x>=b[i]&&a[k].x<=b[j]&&a[k].y>=b[i]&&a[k].y<=b[j])res+=a[k].c;
            gmx(ans,res);
        }
    }
    printf("%lld\n",ans);
}
int main(){
    // maker();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].c);
        if(a[i].x<a[i].y)   swap(a[i].x,a[i].y);
    }
    return baoli(),0;
    sort(a+1,a+n+1,[&](node x,node y){return x.x<y.x;});
    ll now=0;
    for(int i=1;i<=n;i++){
        int j=i;while(j<=n&&a[i].x==a[j].x)now+=a[j].c,j++;j--;
        for(int k=i;k<=j;k++){
            if(s.find(a[k].y)==s.end()){
                auto it=s.upper_bound(a[k].y);
                if(it==s.begin())   s[a[k].y]=0;
                else    s[a[k].y]=(--it)->se;
            }
        }
        for(int k=i;k<=j;k++){
            for(auto &x:s)if(x.fi>=a[k].y)x.se+=a[k].c;
        }
        int lst=0;
        for(auto x:s)gmx(ans,now-a[i].x+x.fi-lst),lst=x.se;
        i=j;
    }
    printf("%lld\n",ans);
}