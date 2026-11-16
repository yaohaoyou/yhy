#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=5e5+10,lgV=29;
int n,m,q;
int pnt;
vector<piii> son[maxn];
int a[maxn];
int fa[maxn],fw[maxn],dep[maxn],X[maxn];
bool vis[maxn],in[maxn];
namespace Graph{
    const int maxm=1e6+10;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int dfn[maxn],tot;
bool ntr[maxn];
namespace stLCA{
    int st[21][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){st[0][dfn[u]=++tot]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(1,0);
        for(int i=1;i<=(31^__builtin_clz(tot));i++)for(int j=1;j+(1<<i)-1<=tot;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=31^__builtin_clz(y-x++);return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using stLCA::LCA;
struct Linear_basis{
    int p[lgV+1],t[lgV+1];
    Linear_basis(){mems(p,0);mems(t,0);}
    void ins(int x,int y){
        for(int i=lgV;~i;i--)if(x&(1<<i)){
            if(!p[i])   return p[i]=x,t[i]=y,void();
            if(y>t[i]){
                swap(p[i],x);
                swap(t[i],y);
            }
            x^=p[i];
        }
    }
    void mrg(Linear_basis &y,int lim=0){for(int i=lgV;~i;i--)if(y.p[i]&&y.t[i]>=lim)ins(y.p[i],y.t[i]);}
    inline int mn(int x,int lim){for(int i=lgV;~i;i--)if(t[i]>=lim)x=min(x,x^p[i]);return x;}
    void rebuild(int lim,int s){
        for(int i=0;i<=lgV;i++)if(t[i]<lim)p[i]=0;
        for(int i=0;i<=lgV;i++)if(p[i])
            for(int j=0;j<i;j++)if((p[i]&(1<<j))||((p[i]&p[j])&s))p[i]^=p[j];
    }
    void print(){for(int i=0;i<=lgV;i++)printf("%d ",p[i]);puts("");}
    inline int kth(int x,int k,int s){
        Linear_basis res;
        int r=0;
        auto add=[&](int a){
            for(int i=lgV;~i;i--)if((a&(1<<i))&&(s&(1<<i))){
                if(!res.p[i]){res.p[i]=a;a=0;break;}
                a^=res.p[i];
            }
            for(int i=lgV;~i;i--)if(a&(1<<i)){
                if(!res.p[i]){res.p[i]=a;r++;break;}
                a^=res.p[i];
            }
        };
        for(int i=lgV;~i;i--)if(p[i])add(p[i]);
        if(k>(1<<r))    return -1;
        for(int i=lgV;~i;i--)if((s&(1<<i))&&!(x&(1<<i))){
            if(!res.p[i])   return -1;
            x^=res.p[i];
        }
        for(int i=lgV;~i;i--)if(res.p[i]&&!(s&(1<<i))){
            r--;
            if(k>(1<<r)){
                k-=(1<<r);
                if(!(x&(1<<i))) x^=res.p[i];
            }
            else if(x&(1<<i))   x^=res.p[i];
        }
        // printf("x = %d\n",x);
        assert((x&s)==s);
        return (x&s)==s?x:-1;
    }
}lb[maxn];
void dfs(int u,int ft,int fr){
    X[u]=X[ft]^fw[u];
    in[u]=vis[u]=true;
    for(auto [t,w]:son[u])if(w.se^fr){
        if(!vis[t]) fa[t]=u,fw[t]=w.fi,dfs(t,u,w.se);
        else if(in[t]){
            int x=u,s=w.fi;pnt++;
            while(x^t){
                ntr[x]=true;
                adde(x,pnt);
                s^=fw[x],x=fa[x];
            }
            adde(t,pnt);a[pnt]=s;
        }
    }
    in[u]=false;
}
void dfs2(int u,int ft){
    dep[u]=dep[ft]+1;
    if(u>n) lb[u].ins(a[u],dep[u]);
    go(u,i)if(t^ft){
        lb[t]=lb[u];
        dfs2(t,u);
    }
}
namespace IO{
template <typename T> T& read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = - f;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	return x *= f;
}
inline int O(int c){return c>=48&&c<112?c-48:-1;}
inline int rd(int x){//Base-64
	int s=0;
	while(x){
		int u=O(getchar());
		if(~u) --x,s=s<<6|u;
	}
	return s;
}
// inline int rd(int x){//Base-10
	// char c=getchar();int s=0;
	// while(!isdigit(c)) c=getchar();
	// while(isdigit(c)) s=s*10+c-48,c=getchar();
	// return s;
// }
inline void outp(int x,int y){//Base-64
    if(y==-1)return printf("-1"),void();
	if(x>1) outp(x-1,y>>6);
	putchar((y&63)+48);
}
// inline void outp(int x,int y){//Base-10
	// printf("%d\n",y);
// }
}
using IO::rd;using IO::outp;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
	n=rd(5),m=rd(5);pnt=n;
    for(int i=1;i<=m;i++){int u=rd(3),v=rd(3),w=rd(5);son[u].eb(v,pii(w,i));son[v].eb(u,pii(w,i));}
    dfs(1,0,0);
    for(int i=2;i<=n;i++)if(!ntr[i])adde(fa[i],i);
    dfs2(1,0);
    stLCA::build();
    q=rd(5);
    while(q--){
        int x=rd(3),y=rd(3),k=rd(5)+1,z=rd(5);
        int s=X[x]^X[y],l=LCA(x,y);
        Linear_basis res;res.mrg(lb[x],dep[l]);res.mrg(lb[y],dep[l]);
        res.rebuild(dep[l],z);
        outp(5,res.kth(s,k,z));
    }
}