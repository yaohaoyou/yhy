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
using namespace std;
const int maxn=5e4+10;
const ll INF=1e18;
int n,q;
int ql,qr;
int a[maxn];
ll b[maxn],ans[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int Log[maxn];
struct ST{
    ll st[20][maxn];
    void build(ll *arr){
        for(int i=2;i<=n+1;i++)   Log[i]=Log[i/2]+1;
        copy(arr,arr+n+1,st[0]);
        for(int i=1;i<=Log[n+1];i++)
            for(int j=0;j+(1<<i)-1<=n;j++)  st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline ll Q(int l,int r){int k=Log[r-l+1];return max(st[k][l],st[k][r-(1<<k)+1]);}
}mx,mn;
void slv(int l,int mid,int r){
    if(r-l+1<ql)    return;
    ll s=-INF;
    for(int i=l;i<=mid;i++){
        int L=max(mid,i+ql-1),R=min(r,i+qr-1);
        if(L<=R)gmx(s,mx.Q(L,R)-b[i-1]);
        gmx(ans[i],s);
    }
    s=-INF;
    for(int i=r;i>mid;i--){
        int L=max(l,i-qr+1),R=min(mid+1,i-ql+1);
        if(L<=R)gmx(s,b[i]+mn.Q(L-1,R-1));
        gmx(ans[i],s);
    }
}
void divide(int l,int r){if(r-l+1<ql)return;if(l==r)return gmx(ans[l],a[l]),void();int mid=(l+r)>>1;slv(l,r,mid);divide(l,mid);divide(mid+1,r);}
int bl[maxn],br[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   b[i]=b[i-1]+a[i];
    mx.build(b);
    for(int i=0;i<=n;i++)b[i]=-b[i];
    mn.build(b);
    for(int i=0;i<=n;i++)b[i]=-b[i];
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&ql,&qr);
        mems(ans,-0x3f);
        ull out=0;
        for(int l=1,r;l<=n;l=r+1){
            r=min(l+qr-1,n);
            if(l^1) slv(l-qr,l-1,r);
            ll s=-INF;
            for(int i=l;i<=r;i++){
                if((i-l)%ql==0) s=-INF;
                int L=i+ql-1,R=min(r,i+qr-1);
                if(L<=R)gmx(s,mx.Q(L,R)-b[i-1]);
                gmx(ans[i],s);
            }
            s=-INF;
            for(int i=r;i>=l;i--){
                int L=max(l,i-qr+1),R=i-ql+1;
                if(L<=R)gmx(s,b[i]+mn.Q(L-1,R-1));
                gmx(ans[i],s);
                if((i-l)%ql==0) s=-INF;
            }
            for(int i=l,j;i<=r;i=j+1){
                j=min(i+ql-1,r);
                if(j-i+1==ql){
                    s=mx.Q(j,r)+mn.Q(l-1,i-1);
                    for(int k=i;k<=j;k++)gmx(ans[k],s);
                }
            }
        }
        for(int i=1;i<=n;i++)   out^=(1ull*i*ans[i]);
        printf("%llu\n",out);
    }
}