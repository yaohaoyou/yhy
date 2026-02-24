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
const int maxn=3e5+10,mod=998244353;
int n;
int cat[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
void init(){
    const int N=3e5;
    cat[0]=1;
    for(int i=1;i<=N;i++)   cat[i]=1ll*cat[i-1]*(4*i-2)%mod*qpow(i+1,mod-2)%mod;
}
struct BIT{
    int tr[maxn<<1];
    inline int lowbit(int x){return x&-x;}
    inline void clear(){for(int i=1;i<=n<<1;i++)tr[i]=0;}
    inline void add(int x,int s){while(x<=n<<1){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
}T;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n<<1
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    // int tim;
    int tag[maxn<<3];
    void build(){for(int i=1;i<=(n<<3);i++)tag[i]=0;}
    void update(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return tag[p]=max(tag[p],s),void();setmid;if(pl<=mid)update(lson,pl,pr,s);if(pr>mid)update(rson,pl,pr,s);}
    int query(int x){
        int p=1,l=1,r=n<<1,ret=tag[p];
        while(l<r){
            setmid;
            if(x<=mid)  p=ls,r=mid;
            else    p=rs,l=mid+1;
            ret=max(ret,tag[p]);
        }
        // printf("ret = (%d,%d)\n",ret.fi,ret.se);
        return ret;
    }
}
using namespace SegmentTree;
int len[maxn<<1];
void matt(){
    scanf("%d",&n);
    for(int i=0;i<=n<<1;i++)    len[i]=0;
    T.clear();build();
    int ans=cat[n];printf("%d ",ans);
    len[0]=n;           
    update(all,1,n<<1,0);
    for(int i=1;i<=n;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        int L=query(l);
        // printf("L = %d,%d\n",L,len[L]);
        len[l]=r-l-1-T.query(l+1,r-1);
        if(L)   T.add(L,-len[l]-2);
        T.add(l,len[l]+2);len[l]>>=1;
        mmul(ans,qpow(cat[len[L]],mod-2));
        len[L]-=len[l]+1;
        // if(!L)  printf("len[0] -= %d\n",len[l]+1);
        mmul(ans,cat[len[L]]);
        // printf("len[%d] = %d\n",l,len[l]);
        mmul(ans,cat[len[l]]);
        printf("%d ",max(1,ans));
        update(all,l,r,l);
    }
    puts("");
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}