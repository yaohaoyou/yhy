#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+10;
const int maxp=maxn*34;
bool mem1;
int n;
int a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
}
using namespace Graph;
namespace IN{
    struct Trie{
        int nex[maxp][2];
        int siz[maxp];
        int tot;
        void insert(int x,int s){
            int p=0;
            for(int i=30;~i;i--){
                if(x&(1<<i)){
                    if(!nex[p][1])  nex[p][1]=++tot;
                    p=nex[p][1];
                }
                else{
                    if(!nex[p][0])  nex[p][0]=++tot;
                    p=nex[p][0];
                }
                siz[p]+=s;
                // printf("add %d\n",p);
            }
        }
        int query(int x){
            int p=0,res=0;
            for(int i=30;~i;i--){
                if(x&(1<<i)){
                    if(siz[nex[p][0]]){res|=(1<<i);p=nex[p][0];}
                    else    p=nex[p][1];
                }
                else{
                    if(siz[nex[p][1]]){res|=(1<<i);p=nex[p][1];}
                    else    p=nex[p][0];
                }
                // printf("que %d\n",p);
            }
            return res;
        }
    }Tr;
    int in[maxn];
    int siz[maxn],son[maxn];
    void clear(int u,int fa){Tr.insert(a[u],-1);for(int i=head[u];i;i=e[i].nxt)if(e[i].to!=fa)clear(e[i].to,u);}
    void ins(int u,int fa){Tr.insert(a[u],1);for(int i=head[u];i;i=e[i].nxt)if(e[i].to!=fa)ins(e[i].to,u);}
    void dfs1(int u,int fa){
        siz[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(t==fa)   continue;
            dfs1(t,u);
            siz[u]+=siz[t];
            if(siz[son[u]]<siz[t])  son[u]=t;
        }
    }
    int dfs3(int u,int fa){
        int res=Tr.query(a[u]);
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(t==fa)   continue;
            res=max(res,dfs3(t,u));
        }
        return res;
    }
    void dfs2(int u,int fa){
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(t==fa||t==son[u])   continue;
            dfs2(t,u);
            in[u]=max(in[u],in[t]);
            clear(t,u);
        }
        if(son[u]){
            dfs2(son[u],u);
            in[u]=max(in[u],in[son[u]]);
        }
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(t==fa||t==son[u])    continue;
            in[u]=max(in[u],dfs3(t,u));
            ins(t,u);
        }
        in[u]=max(in[u],Tr.query(a[u]));Tr.insert(a[u],1);
    }
    void calc_in(){
        dfs1(1,0);
        dfs2(1,0);
    }
}
namespace OUT{
    #define pii pair<int,int>
    #define eb emplace_back
    struct Trie{
        int nex[maxp][2],en[maxp];
        int tot;
        void insert(int x,int id){
            int p=0;
            for(int i=30;~i;i--){
                if(x&(1<<i)){
                    if(!nex[p][1])  nex[p][1]=++tot;
                    p=nex[p][1];
                }
                else{
                    if(!nex[p][0])  nex[p][0]=++tot;
                    p=nex[p][0];
                }
            }
            en[p]=id;
        }
        pii query(int x){
            int p=0;
            int res=0;
            for(int i=30;~i;i--){
                if(x&(1<<i)){
                    if(nex[p][0]){res|=(1<<i);p=nex[p][0];}
                    else    p=nex[p][1];
                }
                else{
                    if(nex[p][1]){res|=(1<<i);p=nex[p][1];}
                    else    p=nex[p][0];
                }
            }
            return pii(res,en[p]);
        }
        void init(){memset(nex,0,sizeof(nex));tot=0;}
    }Tr;
    int out[maxn];
    int P,Q;
    int dfsn[maxn],siz[maxn],rnk[maxn],f[maxn];int cur;
    void dfs(int u,int fa){
        f[u]=fa;
        dfsn[u]=++cur;rnk[cur]=u;siz[u]=1;
        Tr.insert(a[u],u);
        pii res=Tr.query(a[u]);
        if((a[P]^a[Q])<res.first){P=u;Q=res.second;}
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(t==fa)   continue;
            dfs(t,u);siz[u]+=siz[t];
        }
    }
    vector<int> v;
    void calc_out(){
        memset(out,-1,sizeof(out));
        dfs(1,0);Tr.init();
        int p=P;
        while(p){v.eb(p);p=f[p];}reverse(v.begin(),v.end());
        int now=0;
        for(int i=0;i<v.size()-1;i++){
            int u=v[i];
            out[u]=now;
            Tr.insert(a[u],u);now=max(now,Tr.query(a[u]).first);
            for(int j=head[u];j;j=e[j].nxt){
                int t=e[j].to;
                if(t==f[u]||t==v[i+1])  continue;
                for(int k=dfsn[t];k<=dfsn[t]+siz[t]-1;k++){
                    Tr.insert(a[rnk[k]],rnk[k]);
                    now=max(now,Tr.query(a[rnk[k]]).first);
                }
            }
        }
        out[P]=now;
        now=0;
        p=Q;
        v.clear();Tr.init();
        while(p){v.eb(p);p=f[p];}reverse(v.begin(),v.end());
        for(int i=0;i<v.size()-1;i++){
            int u=v[i];
            out[u]=now;
            Tr.insert(a[u],u);now=max(now,Tr.query(a[u]).first);
            for(int j=head[u];j;j=e[j].nxt){
                int t=e[j].to;
                if(t==f[u]||t==v[i+1])  continue;
                for(int k=dfsn[t];k<=dfsn[t]+siz[t]-1;k++){
                    Tr.insert(a[rnk[k]],rnk[k]);
                    now=max(now,Tr.query(a[rnk[k]]).first);
                }
            }
        }
        out[Q]=now;
        for(int i=1;i<=n;i++)   out[i]=out[i]==-1?a[P]^a[Q]:out[i];
    }
}
void dfs1(int u,int fa){
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        a[t]=a[u]^e[i].w;
        dfs1(t,u);
    }
}
bool mem2;
int main(){
    scanf("%d",&n);
    for(int i=1,u,v,w;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    dfs1(1,0);
    IN::calc_in();OUT::calc_out();
    int ans=0;
    for(int i=2;i<=n;i++){
        ans=max(ans,IN::in[i]+OUT::out[i]);
    }
    printf("%d\n",ans);
}