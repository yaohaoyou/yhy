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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e6+10;
int n,tot=1,lst=1;
int fa[maxn];  // link
int ed[maxn],len[maxn],nex[maxn][26];
char s[maxn];
inline void ins(char c){
    int o=c-'a',p=lst,x=++tot;
    ed[x]=1;len[x]=len[p]+1;lst=x;
    while(p&&!nex[p][o])    nex[p][o]=x,p=fa[p];
    if(!p)  return fa[x]=1,void();
    int q=nex[p][o];
    if(len[q]==len[p]+1)    return fa[x]=q,void();
    int nw=++tot;
    memc(nex[nw],nex[q]);len[nw]=len[p]+1;fa[nw]=fa[q];
    fa[q]=fa[x]=nw;
    while(nex[p][o]==q) nex[p][o]=nw,p=fa[p];
}
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
void dfs(int u,int ft){go(u,i)if(t^ft)dfs(t,u),ed[u]+=ed[t];}
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++)   ins(s[i]);
    for(int i=2;i<=tot;i++) add(fa[i],i);
    dfs(1,0);
    ll ans=0;
    for(int i=1;i<=tot;i++)if(ed[i]>1)  gmx(ans,1ll*len[i]*ed[i]);
    printf("%lld\n",ans);
}