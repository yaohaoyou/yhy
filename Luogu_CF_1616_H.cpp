#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define f(x,y) F(x,y,d-1)
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=3e5+10,mod=998244353;
int n,X;
int a[maxn];
int pq[maxn*30];
int nx[maxn*30][2],siz[maxn*30],tot=1;
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
inline int S(int x){return imdel(pq[siz[x]],1);}
inline void ins(int s){
    int p=1;
    for(int i=30;~i;i--){
        siz[p]++;
        bool o=s&(1<<i);
        if(!nx[p][o])   nx[p][o]=++tot;
        p=nx[p][o];
    }
    siz[p]++;
}
int F(int p,int q,int d){
    if(!p||!q)  return 0;
    // printf("%d %d %d : %d %d\n",p,q,d,siz[p],siz[q]);
    if(d<0) return immul(S(p),p==q?1:S(q));
    bool o=X&(1<<d);
    if(!o)  return imadd(f(nx[p][0],nx[q][0]),f(nx[p][1],nx[q][1]));
    if(p==q)    return imadd(f(nx[p][0],nx[p][1]),imadd(S(nx[p][0]),S(nx[p][1])));
    int ans=imadd(immul(S(nx[p][0]),S(nx[q][0])),immul(S(nx[p][1]),S(nx[q][1])));
    int s1=f(nx[p][0],nx[q][1]),s2=f(nx[p][1],nx[q][0]);
    madd(ans,imadd(s1,s2));
    madd(ans,immul(s1,s2));
    madd(ans,immul(s1,imadd(S(nx[p][1]),S(nx[q][0]))));
    madd(ans,immul(s2,imadd(S(nx[p][0]),S(nx[q][1]))));
    return ans;
}
int main(){
    // freopen("xor.in","r",stdin);freopen("xor.out","w",stdout);
    scanf("%d%d",&n,&X);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);ins(a[i]);}
    pq[0]=1;
    for(int i=1;i<=30*n;i++)    pq[i]=(pq[i-1]<<1)%mod;
    printf("%d",F(1,1,30));
}