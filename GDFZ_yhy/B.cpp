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
const int maxn=1.5e5+10;
int n;
int a[maxn],b[maxn],c[maxn];
int aa[maxn],bb[maxn],cc[maxn];
int d[maxn],m1,m2;
vector<int> v[maxn];
set<int> A;
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    pii tr[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=max(tr[p],pii(s,x));while(p>>=1)pu(p);}
    pii query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;pii res=pii(0,0);if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=max(res,query(rson,pl,pr));return res;}
}T[3];
void discrete(){
    for(int i=1;i<=n;i++)   d[i]=c[i];
    sort(d+1,d+n+1);m1=unique(d+1,d+n+1)-d-1;
    memc(cc,d);
    for(int i=1;i<=n;i++)   c[i]=lower_bound(d+1,d+m1+1,c[i])-d;
    
    for(int i=1;i<=n;i++)   d[i]=a[i];
    sort(d+1,d+n+1);m1=unique(d+1,d+n+1)-d-1;
    memc(aa,d);
    for(int i=1;i<=n;i++)   a[i]=lower_bound(d+1,d+m1+1,a[i])-d;

    for(int i=1;i<=n;i++)   d[i]=b[i];
    sort(d+1,d+n+1);m2=unique(d+1,d+n+1)-d-1;
    memc(bb,d);
    for(int i=1;i<=n;i++)   b[i]=lower_bound(d+1,d+m2+1,b[i])-d;
}
// inline int query(int x,int y){
//     int ret=-1e9;
//     for(int i=x+1;i<=n;i++)for(int j=y+1;j<=n;j++)ret=max(ret,mx[i][j]);
//     return ret;
// }
int main(){
    freopen("team.in","r",stdin);freopen("team.out","w",stdout);
    // mems(mx,-0x3f);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d%d",&a[i],&b[i],&c[i]);
    discrete();
    for(int i=1;i<=n;i++)   v[c[i]].eb(i);
    int ans=-1;
    for(int i=1;i<=n;i++){
        for(int j:v[i]){
            // printf("j = %d\n",j);
            // printf("%d %d %d\n",aa[j],bb[j],query(a[j],b[j]));
            pii p=T[2].query(all,a[j]+1,n);
            if(p.fi-aa[p.se]>bb[b[j]])  ans=max(ans,p.fi+cc[c[j]]);
        }
        for(int j:v[i]){
            // printf("j = %d\n",j);
            if(a[j]>1){
                pii t=T[0].query(all,1,a[j]-1);
                if(t.fi>b[j]){
                    // mx[a[j]][t.fi]=max(mx[a[j]][t.fi],aa[a[j]]+bb[t.fi]);
                    T[2].upd(a[j],aa[a[j]]+bb[t.fi]);
                }

            }
            if(b[j]>1){
                pii t=T[1].query(all,1,b[j]-1);
                // printf("%d (%d,%d) %d\n",query(t.fi-1,b[j]-1),t.fi,t.se,b[j]);
                if(t.fi>a[j]){
                    // mx[t.fi][b[j]]=max(mx[t.fi][b[j]],aa[t.fi]+bb[b[j]]);
                    T[2].upd(t.fi,aa[t.fi]+bb[b[j]]);
                    // printf("add2 %d %d : %d\n",t.fi,b[j],aa[t.fi],bb[b[j]]);
                }
            }
            T[0].upd(a[j],b[j]);T[1].upd(b[j],a[j]);
        }
    }
    printf("%d\n",ans);
}