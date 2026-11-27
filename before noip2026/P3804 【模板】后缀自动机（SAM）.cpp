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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e6+10;
int n;
char s[maxn];
int nx[maxn][30],fa[maxn],tim[maxn],len[maxn];
vector<int> son[maxn];
int tot=1,lst=1;
void ins(char c){
    int o=c-'a',p=lst,x=++tot;lst=x;
    tim[x]=1;len[x]=len[p]+1;
    while(p&&!nx[p][o])    nx[p][o]=x,p=fa[p];
    if(!p)  return fa[x]=1,void();
    int q=nx[p][o];
    if(len[q]==len[p]+1)    return fa[x]=q,void();
    int nw=++tot;
    memc(nx[nw],nx[q]);len[nw]=len[p]+1;fa[nw]=fa[q];
    fa[q]=fa[x]=nw;
    while(nx[p][o]==q)  nx[p][o]=nw,p=fa[p];
}
void dfs(int u){for(int t:son[u])dfs(t),tim[u]+=tim[t];}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++)   ins(s[i]);
    for(int i=2;i<=tot;i++)   son[fa[i]].eb(i);
    dfs(1);
    ll ans=0;for(int i=1;i<=tot;i++)if(tim[i]>1)gmx(ans,1ll*len[i]*tim[i]);
    printf("%lld\n",ans);
}