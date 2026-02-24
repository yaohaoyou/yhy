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
const int maxn=20,maxN=(1<<17)+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
namespace Graph{
const int maxm=maxn*maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int n,m;
int w[maxN],f[maxN],g[maxN],ou[maxN],qp[maxn*maxn];
int main(){
    scanf("%d%d",&n,&m);const int N=(1<<n)-1;
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);ou[1<<u-1]|=(1<<v-1);ou[1<<v-1]|=(1<<u-1);}
    qp[0]=1;for(int i=1;i<=m;i++)   qp[i]=imadd(qp[i-1],qp[i-1]);
    for(int i=0;i<=N;i++){
        for(int u=1;u<=n;u++){
            if(!(i&(1<<u-1)))   continue;
            ou[i]=ou[i^(1<<u-1)]|ou[1<<u-1];
            w[i]=w[i^(1<<u-1)];
            go(u,_)
                if(i&(1<<t-1))  w[i]++;
            break;
        }
    }
    for(int s=0;s<=N;s++)   f[s]=g[s]=qp[w[s]];
    f[1]=1;
    for(int s=0;s<=N;s++){
        if(!(s&1)){f[s]=0;continue;}
        for(int t=s&(s-1);t;t=(t-1)&s){
            mdel(f[s],immul(qp[w[s^t]],f[t]));
        }
    }
    g[2]=1;
    for(int s=0;s<=N;s++){
        if(!(s&2)){g[s]=0;continue;}
        for(int t=s&(s-1);t;t=(t-1)&s)
            mdel(g[s],immul(qp[w[s^t]],g[t]));
    }
    // for(int i=0;i<=N;i++)   printf("%d %d\n",f[i],g[i]);
    int ans=qp[m];
    for(int s=0;s<=N;s++){
        int ss=N^s;
        for(int t=ss;t;t=(t-1)&ss){
            if(ou[s]&t) continue;
            // printf("%d %d : %d\n",s,t,1ll*f[s]*g[t]%mod*qp[w[N^s^t])%mod);
            mdel(ans,1ll*f[s]*g[t]%mod*qp[w[N^s^t]]%mod);
        }
    }
    printf("%d\n",ans);
}