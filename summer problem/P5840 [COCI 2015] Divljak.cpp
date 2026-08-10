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
const int maxn=1e5+10,maxs=2e6+10;
int n;
char s[maxs];
vector<int> vec;
namespace Graph{
    const int maxm=maxs;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxs];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int dfn[maxs],siz[maxs],tot;
namespace st_LCA{
    int st[21][maxs],Log[maxs];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){st[0][dfn[u]=++tot]=ft;siz[u]=1;go(u,i)dfs(t,u),siz[u]+=siz[t];}
    void build(){
        dfs(0,0);
        for(int i=2;i<=tot;i++) Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[tot];i++)
            for(int j=1;j+(1<<i)-1<=tot;j++)    st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using st_LCA::LCA;
struct ACAM{
    int cnt;
    int nex[maxs][26],en[maxn],fail[maxs];
    inline void ins(int id){
        int p=0,len=strlen(s+1);
        for(int i=1;i<=len;i++){
            int o=s[i]-'a',&t=nex[p][o];
            if(!t)  t=++cnt;
            p=t;
        }
        en[id]=p;
    }
    inline void query(){
        vec.clear();
        int len=strlen(s+1);
        int p=0;
        for(int i=1;i<=len;i++) vec.eb(p=nex[p][s[i]-'a']);
    }
    queue<int> q;
    void build(){
        for(int i=0;i<26;i++)if(nex[0][i])q.ep(nex[0][i]);
        while(!q.empty()){
            int u=q.front();q.pop();add(fail[u],u);
            for(int i=0;i<26;i++){
                if(nex[u][i]){q.ep(nex[u][i]);fail[nex[u][i]]=nex[fail[u]][i];}
                else    nex[u][i]=nex[fail[u]][i];
            }
        }
    }
}A;
struct BIT{
    int tr[maxs];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=tot){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
}T;
inline void upd(int x,int s){T.add(dfn[x],s);}
inline int query(int x){return T.query(dfn[x],dfn[x]+siz[x]-1);}
int main(){
    scanf("%d",&n);for(int i=1;i<=n;i++){scanf("%s",s+1);A.ins(i);}
    A.build();st_LCA::build();
    int q;scanf("%d",&q);
    while(q--){
        int op,x;scanf("%d",&op);
        if(op==1){
            scanf("%s",s+1);
            A.query();
            sort(vec.begin(),vec.end(),[&](int x,int y){return dfn[x]<dfn[y];});
            for(int i:vec)  upd(i,1);
            for(int i=0;i+1<vec.size();i++) upd(LCA(vec[i],vec[i+1]),-1);
        }
        else{
            scanf("%d",&x);
            printf("%d\n",query(A.en[x]));
        }
    }
}