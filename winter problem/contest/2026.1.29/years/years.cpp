#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pil pair<int,ll>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10;
int n,m;
ll a[maxn];
int deg[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);putc('\n');}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;bool ontr;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v,false};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=deg[i]=0;cnt=1;}
}
using namespace Graph;
int rt;bool flag;
int dep[maxn],fa[maxn];ll dp[maxn][2];
bool vis[maxn];
queue<int> leaf;
vector<int> d2;
vector<piii> out;
void dfs(int u,int ft){
    dep[u]=dep[fa[u]=ft]+1;dp[u][0]=dp[u][1]=0;dp[u][dep[u]&1]=a[u];
    go(u,i){
        if(t==ft)   continue;
        if(e[i].ontr){
            dfs(t,u);
            dp[u][0]+=dp[t][0];dp[u][1]+=dp[t][1];
        }
    }
}
void dfs2(int u,int ft){dep[u]=dep[fa[u]=ft]+1;if(dep[u]==2)d2.eb(u);bool lf=true;go(u,i)if((t^ft)&&(e[i].ontr))dfs2(t,u),lf=false;if(lf&&fa[fa[u]])leaf.ep(u);}
void dfs3(int u,int ft){
    dep[u]=dep[ft]+1;dp[u][0]=dp[u][1]=0;dp[u][dep[u]&1]=a[u];
    vis[u]=true;
    go(u,i){
        if(t==ft)   continue;
        if(!vis[t]){
            dfs3(t,u);
            dp[u][0]+=dp[t][0];dp[u][1]+=dp[t][1];
        }
        else if((dep[t]&1)==(dep[u]&1)&&dep[t]<dep[u]&&out.empty()){out.eb(pii(t,u),ft);}
    }
}
void dfs4(int u,int ft){vis[u]=true;go(u,i)if(!vis[t])e[i].ontr=true,dfs4(t,u);}
void solvetree(int add,int RT){
    fill(dep+1,dep+n+1,0);dfs(1,0);if(abs(dp[1][0])&1)return pus("No"),void();
    int rt=RT;if(!rt){for(int i=1;i<=n;i++)if(deg[i]>2){rt=i;break;}}
    if(rt){
        d2.clear();queue<int>().swap(leaf);
        pus("Yes");print(n-1+add,'\n');
        dfs2(rt,0);//printf("leaf = %d,%d\n",leaf.size(),d2.size());
        while(!leaf.empty()){
            int u=leaf.front();leaf.pop();
            print(u,' ');print(fa[u],' ');print(fa[fa[u]],' ');print(-a[u],'\n');
            a[fa[u]]+=2*a[u];a[fa[fa[u]]]-=a[u];a[u]=0;
            if(fa[fa[fa[u]]]&&((--deg[fa[u]])==1))   leaf.ep(fa[u]);
        }
        while(d2.size()>3){
            int u=d2.back();d2.pop_back();
            print(u,' ');print(fa[u],' ');print(d2[0],' ');print(-a[u],'\n');
            a[rt]+=2*a[u];a[d2[0]]-=a[u];a[u]=0;
        }
        int u=d2[0],v=d2[1],w=d2[2];
        if(a[v]%2==0)   swap(u,v);
        if(a[w]%2==0)   swap(u,w);
        ll c=(a[u]+a[v]-a[w])/2,d=(a[u]-a[v]+a[w])/2;
        print(u,' ');print(fa[u],' ');print(v,' ');print(-c,'\n');
        a[rt]+=c+c;a[u]-=c;a[v]-=c;
        print(u,' ');print(fa[u],' ');print(w,' ');print(-d,'\n');
        a[rt]+=d+d;a[u]-=d;a[w]-=d;
        print(v,' ');print(rt,' ');print(w,' ');print(a[rt]/2,'\n');
    }
    else{
        int rt=0;for(int i=1;i<=n;i++)if(deg[i]==1){rt=i;break;}
        dfs2(rt,0);d2.clear();
        vector<pil> ans;
        int u=leaf.front();leaf.pop();
        while(fa[fa[u]]){
            ans.eb(u,-a[u]);
            a[fa[u]]+=2*a[u];a[fa[fa[u]]]-=a[u];
            u=fa[u];
        }
        if(!a[u]&&!a[rt]){
            pus("Yes");
            print(ans.size()+add,'\n');
            for(auto [u,j]:ans){print(u,' ');print(fa[u],' ');print(fa[fa[u]],' ');print(j,'\n');}
        }
        else pus("No");
    }
}
struct node{
    ll k,b;
    inline node operator+(ll x){return (node){k,b+x};}
    inline node operator-(ll x){return (node){k,b-x};}
    inline node operator+(node x){return (node){k+x.k,b+x.b};}
    inline node operator-(node x){return (node){k-x.k,b-x.b};}
    inline node operator*(ll x){return (node){k*x,b*x};}
};
node f[maxn];
vector<int> cir;
void dfscir(int u,int ft){cir.eb(u);go(u,i)if((t^ft)&&(cir.size()^n))dfscir(t,u);}
void solvecircle(){
    cir.clear();
    f[1]={0,0};dfscir(1,0);f[cir[1]]={1,0};
    for(int i=2;i<cir.size();i++){
        f[cir[i]]=f[cir[i-1]]*2-f[cir[i-2]]-a[cir[i-1]];
    }
    node res=f[1]*2-f[cir.back()]-a[1];
    if(res.b%abs(1-res.k)) return pus("No"),void();
    pus("Yes");
    print(n-1,'\n');
    ll c1=res.b/(1-res.k);
    print(1,' ');print(cir[1],' ');print(cir[2],' ');print(c1,'\n');
    for(int i=2;i<cir.size();i++){
        print(cir[i-1],' ');print(cir[i],' ');print(cir[(i+1)%cir.size()],' ');print(c1*f[cir[i]].k+f[cir[i]].b,'\n');
    }
}
queue<int> que;
void matt(int _cases){
    rebuild();
    n=read();m=read();
    fill(vis+1,vis+n+1,0);
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   a[i]-=read();
    for(int i=1;i<=m;i++)   adde(read(),read());
    if(accumulate(a+1,a+n+1,0ll))    return pus("No"),void();
    if(m==n-1){
        for(int i=2;i<=cnt;i++)e[i].ontr=true;
        return solvetree(0,0);
    }
    out.clear();
    rt=max_element(deg+1,deg+n+1)-deg;
    // debug("rt = %d\n",rt);
    if(deg[rt]>=3){
        {
            fill(vis+1,vis+n+1,0);fill(deg+1,deg+n+1,0);
            queue<int>().swap(que);que.ep(rt);vis[rt]=true;
            while(!que.empty()){
                int u=que.front();que.pop();
                go(u,i){
                    if(vis[t])  continue;
                    deg[u]++;deg[t]++;
                    e[i].ontr=e[i^1].ontr=true;
                    que.ep(t);vis[t]=true;
                }
            }
            dfs(rt,0);
            for(int i=2;i<=cnt;i++){
                int u=e[i].to,t=e[i^1].to;
                if((dep[t]&1)==(dep[u]&1)){out.eb(pii(t,u),fa[u]);break;}
            }
        }
        // debug("rt = %d\n",rt);
        if(!(abs(dp[rt][0])&1)){
            // debug("bipartite\n");
            solvetree(0,rt);
            return;
        }
        else if(!out.empty()){
            // debug("rt = %d\n",rt);
            // printf("%d\n",dp[rt][0]);
            a[out[0].fi.fi]++;a[out[0].fi.se]-=2;a[out[0].se]++;
            solvetree(1,rt);
            print(out[0].fi.fi,' ');print(out[0].fi.se,' ');print(out[0].se,' ');print(1,'\n');
            out.clear();
        }
        else pus("No");
        return;
    }
    solvecircle();
}
int main(){freopen("years.in","r",stdin);freopen("years.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);flush();}