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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=4e5+10,B=700,Block=maxn/B+10,mod=998244353;
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
int lst=1,tot=1;
char s[maxn];
int en[maxn],ed[maxn],len[maxn],fa[maxn],nex[maxn][26];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int buc[Block],id[maxn],bl[Block],br[Block],bel[maxn];
void init(){
    for(int i=1;i<=tot;i++)   id[i]=(i-1)/B+1;
    for(int i=1;i<=id[tot];i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,tot);
}
inline void upd(int x,int s){
    for(int i=x;i>=bl[id[x]];i--){
        if(bel[i])  return;
        bel[i]=s;
    }
    buc[id[x]]=-1;
    x=id[x]-1;
    while(x&&!buc[x])   buc[x--]=s;
    x=br[x];
    while(x&&!bel[x])   bel[x--]=s;
}
inline void era(int x,int s){
    for(int i=x;i>=bl[id[x]];i--){
        if(bel[i]^s)    return;
        bel[i]=0;
    }
    buc[id[x]]=0;
    x=id[x]-1;
    while(x&&buc[x]==s) buc[x--]=0;
    x=br[x];
    while(x&&bel[x]==s) bel[x--]=0;
}
void ins(char c,int id){
    int o=c-'a',p=lst,x=++tot;lst=en[id]=x;
    ed[x]=id;len[x]=len[p]+1;
    while(!nex[p][o])   nex[p][o]=x,p=fa[p];
    if(!p)  return fa[x]=1,void();
    int q=nex[p][o];
    if(len[q]==len[p]+1)    return fa[x]=q,void();
    int nw=++tot;memc(nex[nw],nex[q]);len[nw]=len[p]+1;fa[nw]=fa[q];
    fa[q]=fa[x]=nw;
    while(nex[p][o]==q) nex[p][o]=nw,p=fa[p];
}
int ans;
int sum[maxn],f[maxn],g[maxn];
vector<int> tag[maxn];
inline int calc(int R,int x){
    ull res=0;
    gmn(R,x);
    for(int l=1,r;l<=R;l=r+1){
        r=min(R,x/(x/l));
        res+=1ull*(x/l)*(r-l+1);
    }
    return res%mod;
}
void dfs(int u){
    int cc=0;
    upd(len[u],u);
    if(ed[u]){
        sum[u]=1;
        cc=f[u]=calc(len[u],ed[u]);
        g[u]=ed[u]/len[u];
        int i=ed[u];
        for(int l=1,r;l<=i;l=r+1){
            r=i/(i/l);
            if(r>=i)    continue;
            int x=bel[r+1];
            if(buc[id[r+1]]!=-1&&buc[id[r+1]])    x=buc[id[r+1]];
            if(tag[x].empty()||tag[x].back()!=i)    tag[x].eb(i);
        }
    }
    go(u,_){
        dfs(t);
        sum[u]+=sum[t];
        madd(g[u],g[t]);
        madd(f[u],f[t]);
    }
    go(u,_)if(f[t])madd(ans,immul(sum[u]-sum[t],f[t]));
    if(ed[u])   madd(ans,immul(sum[u],cc));
    if(len[fa[u]]){
        for(int i:tag[u])   mdel(g[u],i/len[u]);
        mdel(f[u],immul(len[u]-len[fa[u]],g[u]));
        ull res=0;
        for(int i:tag[u]){
            madd(g[u],i/len[fa[u]]);
            for(int l=len[fa[u]]+1,r;l<=min(i,len[u]);l=r+1){
                r=min(i/(i/l),len[u]);
                res+=1ull*(r-l+1)*(i/l);
            }
        }
        mdel(f[u],res%mod);
    }
    else f[u]=0;
    era(len[u],u);
}
void data(){
    for(int i=1;i<=100000;i++)printf("a");
    puts("");
    exit(0);
}
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++)   ins(s[i],i);
    for(int i=2;i<=tot;i++) add(fa[i],i);
    init();
    dfs(1);
    printf("%d\n",ans);
}