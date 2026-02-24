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
const int maxn=2e6+10,base=3;
int n,mod,m1,m2;
int a[maxn],b[maxn],p[maxn];
ull pq[maxn];
bool dp[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
vector<int> fac;
struct BIT{
    ull tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ull s){x++;while(x<=mod+mod){tr[x]+=s;x+=lowbit(x);}}
    inline ull que(int x){x++;ull res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ull query(int l,int r){return que(r)-que(l-1);}
}T;
void makefactors(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0){fac.eb(i);while(x%i==0)x/=i;}
    }
    if(x^1) fac.eb(x);
}
inline ull mul(ull x,ull y){return x*y;}
int main(){
    scanf("%d%d",&mod,&n);
    for(int i=1;i<=n;i++){
        int x,y;scanf("%d%d",&x,&y);
        if(!x)  a[++m1]=y;
        else    b[++m2]=y;
    }
    makefactors(mod-1);
    int g=2;while(true){
        bool flag=true;
        for(int i:fac)if(qpow(g,(mod-1)/i)==1){flag=false;break;}
        if(flag)break;
        g++;
    }
    sort(a+1,a+m1+1);sort(b+1,b+m2+1);
    for(int i=0;i<=mod-2;i++)   p[qpow(g,i)]=i;
    for(int i=1;i<=m1;i++)if(a[i])dp[p[a[i]]]=true;
    mod--;
    pq[0]=1;for(int i=1;i<=mod+mod;i++) pq[i]=pq[i-1]*base;
    for(int i=0;i<mod;i++)if(dp[i])T.add(i,pq[i]),T.add(i+mod,pq[i+mod]);
    vector<int> add;
    for(int i=1;i<=m2;i++){
        if(!b[i])   continue;
        add.clear();
        int L=0,R=p[b[i]];
        while(L<mod){
            int l=1,r=mod-L,x=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(mul(T.query(L,L+mid-1),pq[R-L])==T.query(R,R+mid-1))  l=mid+1;
                else x=mid,r=mid-1;
            }
            if(x){
                x=L+x-1;int y=(x+p[b[i]])%mod;
                assert(dp[x]^dp[y]);
                if(dp[x]&&!dp[y])   add.eb(y);
                L=x+1;R=L+p[b[i]];
            }
            else break;
        }
        for(int y:add){
            dp[y]=true;
            T.add(y,pq[y]);
            T.add(y+mod,pq[y+mod]);
        }
    }
    printf("%d\n",count(dp,dp+mod,0)+(a[1]&&b[1]));
}