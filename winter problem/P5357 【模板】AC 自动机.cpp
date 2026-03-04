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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2e5+10,maxs=2e6+10;
bool mem1;
int n;
int ans[maxn];
char a[maxs];
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
namespace AC{
    int tot;
    int nex[maxn][26],fail[maxn],sum[maxn];
    vector<int> en[maxn];
    queue<int> q;
    inline void ins(char *s,int id){
        int len=strlen(s+1),p=0;
        for(int i=1;i<=len;i++){
            int o=s[i]-'a',&t=nex[p][o];
            if(!t)  t=++tot;
            p=t;
        }
        en[p].eb(id);
    }
    void build(){
        for(int i=0;i<26;i++)if(nex[0][i])q.ep(nex[0][i]);
        while(!q.empty()){
            int u=q.front();q.pop();
            add(fail[u],u);
            for(int i=0;i<26;i++){
                int &t=nex[u][i];
                if(!t)  t=nex[fail[u]][i];
                else    fail[t]=nex[fail[u]][i],q.ep(t);
            }
        }
    }
    void query(char *s){
        int len=strlen(s+1),p=0;
        for(int i=1;i<=len;i++){
            sum[p]++;
            int o=s[i]-'a';
            p=nex[p][o];
        }
        sum[p]++;
    }
    void dfs(int u){go(u,i)dfs(t),sum[u]+=sum[t];for(int i:en[u])ans[i]=sum[u];}
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",a+1);
        AC::ins(a,i);
    }
    AC::build();scanf("%s",a+1);AC::query(a);AC::dfs(0);
    for(int i=1;i<=n;i++)   printf("%d\n",ans[i]);
}