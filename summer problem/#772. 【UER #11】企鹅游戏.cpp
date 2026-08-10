#include<bits/stdc++.h>
#define ui unsigned int
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e6+10,B=(1<<20),maxp=2e6+10;
ui p0[maxn],p1[maxn];
namespace FastMod{
    inline void madd(ui &x,ui y){x+=y;}
    inline void mdel(ui &x,ui y){x-=y;}
    inline void mmul(ui &x,ui y){x*=y;}
    inline ui imadd(ui x,ui y){madd(x,y);return x;}
    inline ui imdel(ui x,ui y){mdel(x,y);return x;}
    inline ui immul(ui x,ui y){mmul(x,y);return x;}
    // inline ui qpow(ui x,ll y){ui res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
    inline ui qpow(ll y){return immul(p1[y>>20],p0[y&(B-1)]);}
}
using namespace FastMod;
int n,m;
char s[maxn];
int v[maxn],f[maxn],g[maxn],h[maxn];
int vec[maxn],vl;
ui ans;
ll sum=0;
namespace AC{
    int tot;
    int c[maxp],nex[maxp][26],fail[maxp],en[maxn],fa[maxp];
    void clear(){for(int i=0;i<=tot;i++)mems(nex[i],0);tot=0;}
    void ins(int id){
        int len=strlen(s+1),p=0;
        for(int i=1;i<=len;i++){
            int o=s[i]-'a',&t=nex[p][o];
            if(!t)  t=++tot;
            p=t;
        }
        c[p]=id;en[id]=p;
    }
    queue<int> q;
    void build(){
        for(int i=0;i<26;i++)if(nex[0][i])q.ep(nex[0][i]);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=0;i<26;i++){
                int &t=nex[u][i];
                if(!t)  t=nex[fail[u]][i];
                else    fail[t]=nex[fail[u]][i],q.ep(t),fa[t]=c[fail[t]]?c[fail[t]]:fa[fail[t]];
            }
        }
    }
    // void dfs(int u){
    //     go(u,i)dfs(t),g[u]+=g[t],f[t]=g[t]=0;
    //     f[u]+=g[u];
    //     if(u)   madd(ans,qpow(1ll*u*f[u])),ans--;
    //     head[u]=0;
    // }
    ui query(){
        int p=0,len=strlen(s+1);
        for(int i=1;i<=len;i++){
            int o=s[i]-'a';
            p=nex[p][o];
            if(c[p]){
                if(!h[c[p]])    v[++v[0]]=c[p];
                h[c[p]]++;
            }
            else{
                if(!h[fa[p]])    v[++v[0]]=fa[p];
                h[fa[p]]++;
            }
        }
        ans=n;
        vl=0;
        for(int i=1;i<=v[0];i++){
            int x=v[i],u=x,bef=vl;
            while(u&&!f[u])    f[u]+=h[x],vec[++vl]=u,u=fa[en[u]];
            reverse(vec+bef+1,vec+vl+1);
            if(u)   g[u]+=h[x];
            h[x]=0;
        }
        for(int i=vl;i;i--){
            int u=vec[i];
            g[fa[en[u]]]+=g[u];f[u]+=g[u];
            if(u)madd(ans,qpow(1ll*u*f[u])),ans--;
            f[u]=g[u]=0;
        }
        v[0]=0;
        return ans;
    }
}
void matt(int _cases){
    p0[0]=1;for(int i=1;i<=B;i++)p0[i]=immul(3,p0[i-1]);
    p1[0]=1;for(int i=1;i<=B;i++)p1[i]=immul(p0[B],p1[i-1]);
    AC::clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        AC::ins(i);
    }
    AC::build();
    for(int i=1;i<=m;i++){
        scanf("%s",s+1);
        printf("%u\n",AC::query());
    }
}
int main(){scanf("%*d");int T=1;for(int i=1;i<=T;i++)matt(i);}