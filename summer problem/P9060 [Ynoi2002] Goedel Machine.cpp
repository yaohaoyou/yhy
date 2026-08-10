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
const int maxn=1e5+10,B=450,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y,int p=mod){int res=1;while(y){if(y&1)res=1ll*res*x%p;x=1ll*x*x%p;y>>=1;}return res;}
}
using namespace FastMod;
int n,q;
int a[maxn];
vector<pii> fac[maxn];
struct ques{int l,r,id;}Q[maxn];
int out[maxn];
int vis[maxn];
int ans=1;
inline void add(int x){
    for(auto [i,j]:fac[x]){
        for(int k=1,now=i;k<=j;k++,now*=i)
            mmul(ans,qpow(i,qpow(2,vis[now],mod-1))),vis[now]++;
    }
}
inline void del(int x){
    for(auto [i,j]:fac[x]){
        for(int k=1,now=i;k<=j;k++,now*=i)
            vis[now]--,mmul(ans,qpow(qpow(i,qpow(2,vis[now],mod-1),mod-1),mod-2));
    }
}
void makefactors(int x,int id){
    for(int i=2;1ll*i*i<=x;i++){
        if(x%i==0){
            int c=0;while(x%i==0)x/=i,c++;
            fac[id].eb(i,c);
        }
    }
    if(x^1) fac[id].eb(x,1);
}
int main(){
    scanf("%d%d",&n,&q);
    assert(n<=1000);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=q;i++)   scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
    for(int i=1;i<=n;i++)   makefactors(a[i],i);
    sort(Q+1,Q+q+1,[&](ques x,ques y){return (x.l/B==y.l/B)?(x.r==y.r?0:((x.l/B)&1)^(x.r<y.r)):(x.l<y.l);});
    for(int i=1,l=1,r=0;i<=q;i++){
        auto [ql,qr,id]=Q[i];
        while(l>ql)add(--l);
        while(r<qr)add(++r);
        while(l<ql)del(l++);
        while(r>qr)del(r--);
        out[id]=ans;
    }
    for(int i=1;i<=q;i++)   printf("%d\n",out[i]);
}
//