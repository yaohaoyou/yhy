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
const int maxn=2e5+10;
int n,m,q;
string s[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int fa[maxn],dep[maxn];
char fc[maxn];
vector<int> nxt[maxn];
void dfs(int u,int ft){
    fa[u]=ft;dep[u]=dep[ft]+1;
    go(u,i)if(t^ft){
        fc[t]=w;
        dfs(t,u);
    }
}
int main(){
    freopen("rune.in","r",stdin);freopen("rune.out","w",stdout);
    cin>>n>>m>>q;
    for(int i=1;i<n;i++){int u,v;char s;cin>>u>>v>>s;adde(u,v,s);}
    for(int i=1;i<=m;i++){
        cin>>s[i];
        nxt[i].resize(s[i].length());
        nxt[i][0]=-1;
        for(int j=1;j<s[i].length();j++){
            int k=nxt[i][j-1];
            while(k!=-1&&s[i][k+1]!=s[i][j])    k=nxt[i][k];
            if(s[i][k+1]==s[i][j])  k++;
            nxt[i][j]=k;
        }
    }
    dfs(1,0);
    while(q--){
        int u,v,p;cin>>u>>v>>p;
        string s1="",s2="";bool flag=false;
        if(dep[u]<dep[v])   swap(u,v),flag=true;
        while(dep[u]>dep[v])s1+=fc[u],u=fa[u];
        while(u^v)s1+=fc[u],s2+=fc[v],u=fa[u],v=fa[v];
        reverse(s2.begin(),s2.end());s1+=s2;
        if(flag)    reverse(s1.begin(),s1.end());
        int ans=0;
        for(int i=0,j=-1;i<s1.length();i++){
            while(j!=-1&&s[p][j+1]!=s1[i])  j=nxt[p][j];
            if(s[p][j+1]==s1[i])    j++;
            if(j==s[p].length()-1)  j=nxt[p][j],ans++;
        }
        printf("%d\n",ans);
    }
}