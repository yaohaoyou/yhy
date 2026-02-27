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
const int maxn=2e5+10,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn],nx[maxn];
struct st{
    int Log[maxn];
    pii st[20][maxn];
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=pii(a[i]>0?1e9:a[i]-i,i);
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline pii query(int l,int r){int k=Log[r-l+1];return max(st[k][l],st[k][r-(1<<k)+1]);}
}st;
inline int sum(int l,int r){return 1ll*(l+r)*(r-l+1)/2%mod;}
void matt(int _cases){
    for(int i=1;i<=n;i++)nx[i]=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);a[n+1]=0;
    st.build();nx[n+1]=n+1;
    for(int i=n;i;i--)  nx[i]=a[i+1]>0?i+1:nx[i+1];
    int ans=0;
    for(int i=1;i<=n;i++){
        if(a[i]<=0) continue;
        madd(ans,immul(i,sum(a[i],a[i]+nx[i]-i-1)));
        madd(ans,1ull*i*(a[i]+nx[i]-i-1)*(n-nx[i]+1)%mod);
    }
    for(int i=1;i<=n;i++){
        if(a[i]>0)  continue;
        // r<nx[i]
        int l=1,r=i,L=i;
        while(l<=r){
            int mid=(l+r)>>1;
            if(st.query(mid,i).se==i)   L=mid,r=mid-1;
            else l=mid+1;
        }
        l=i,r=n;int R=i;
        while(l<=r){
            int mid=(l+r)>>1;
            if(st.query(i,mid).se==i)   R=mid,l=mid+1;
            else r=mid-1;
        }
        // printf("[%d,%d]\n",L,R);
        if(R+1==nx[i]){
            if(a[i]+R-i>0){
                int res=0;
                madd(res,immul(i-L+1,sum(1,a[i]+R-i)));
                madd(res,1ull*(i-L+1)*(n-R)*(a[i]+R-i)%mod);
                madd(ans,res);
                // printf("%d\n",res);
            }
        }
        else if(a[i]+R-i>0)  madd(ans,immul(i-L+1,sum(1,a[i]+R-i)));
    }
    // for(int l=1;l<=n;l++){
    //     for(int r=l;r<=n;r++){
    //         ll res=0;
    //         if(a[l]>0){
    //             int x=l;
    //             while(x<=r){
    //                 res+=a[x]+min(nx[x],r+1)-x-1;
    //                 x=nx[x];
    //             }
    //         }
    //         else if(l^r){
    //             int R=min(r+1,nx[l]),p=st.query(l,R-1).se;
    //             res=max(a[p]+R-p-1,0);
    //             int x=nx[l];
    //             while(x<=r){
    //                 res+=a[x]+min(nx[x],r+1)-x-1;
    //                 x=nx[x];
    //             }
    //         }
    //         // printf("res = %lld\n",res);
    //         madd(ans,res%mod);
    //     }
    // }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}