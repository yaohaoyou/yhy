#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,u) memset(arr,u,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10;
int n,q;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(u,i) for(int i=head[u];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
struct my_multiset{
    priority_queue<int> q1,q2;
    inline void emplace(int x){q1.ep(x);}
    inline void erase(int x){q2.ep(x);}
    inline int size(){return q1.size()-q2.size();}
    inline bool empty(){return q1.size()==q2.size();}
    inline int top(){while(!q2.empty()&&q1.top()==q2.top())q1.pop(),q2.pop();return q1.top();}
    inline int second(){int x=top();q1.pop();int y=top();q1.ep(x);return y;}
};
my_multiset A,B[maxn],C[maxn];
int all,rt;
int siz[maxn],fa[maxn];
bool vis[maxn],on[maxn];
namespace ST_LCA{
    const int lgV=19;
    int tot;
    int dep[maxn];
    int dfn[maxn],st[lgV+1][maxn],Log[maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){
        dep[u]=dep[ft]+1;
        st[0][dfn[u]=++tot]=ft;
        go(u,i){
            int t=e[i].to;
            if(t==ft)   continue;
            dfs(t,u);
        }
    }
    void build(){
        dfs(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=lgV;i++)
            for(int j=1;j+(1<<i)-1<=n;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y){return dep[x]+dep[y]-(dep[LCA(x,y)]<<1);}
}
using ST_LCA::dis;
void getWC(int u,int ft){
    int mx=0;
    siz[u]=1;
    go(u,i){
        int t=e[i].to;
        if(t==ft||vis[t])   continue;
        getWC(t,u);
        siz[u]+=siz[t];
        mx=max(mx,siz[t]);
    }
    mx=max(mx,all-siz[u]);
    if(mx*2<=all)   rt=u;
}
void divide(int u){
    vis[u]=true;
    getWC(u,0);
    go(u,i){
        int t=e[i].to;
        if(vis[t])   continue;
        all=siz[t];getWC(t,u);fa[rt]=u;divide(rt);
    }
}
inline void upd(int x){
    if(B[x].size()<2) return;
    A.ep(B[x].top()+B[x].second());
}
inline void del(int x){
    if(B[x].size()<2) return;
    A.erase(B[x].top()+B[x].second());
}
int ctt;
inline void lightup(int u){
    ctt++;
    int x=u;
    del(u);B[u].ep(0);upd(u);
    while(fa[u]){
        del(fa[u]);
        if(!C[u].empty())   B[fa[u]].erase(C[u].top());
        C[u].ep(dis(fa[u],x));
        if(!C[u].empty())   B[fa[u]].ep(C[u].top());
        upd(fa[u]);
        u=fa[u];
    }
}
inline void lightdown(int u){
    ctt--;
    int x=u;
    del(u);B[u].erase(0);upd(u);
    while(fa[u]){
        del(fa[u]);
        if(!C[u].empty())  B[fa[u]].erase(C[u].top());
        C[u].erase(dis(fa[u],x));
        if(!C[u].empty())  B[fa[u]].ep(C[u].top());
        upd(fa[u]);
        u=fa[u];
    }
}
int main(){
    n=read();
    for(int i=1;i<n;i++)    adde(read(),read());
    ST_LCA::build();
    all=n;getWC(1,0);divide(rt);
    for(int i=1;i<=n;i++)   lightup(i),on[i]=true;
    q=read();
    while(q--){
        char c='A';int u;
        while(c!='C'&&c!='G')   c=getc();
        if(c=='C'){
            u=read();
            if(!on[u])  lightup(u);
            else    lightdown(u);
            on[u]^=1;
        }
        else    print(A.empty()?ctt?0:-1:A.top()),putc('\n');
        // for(int j:B[3])  debug("%d ",j);debug("\n");
    }
    flush();
}