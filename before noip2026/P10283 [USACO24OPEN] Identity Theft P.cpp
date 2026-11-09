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
const int maxn=1e6+10;
int n,tot;
ll ans;
char s[maxn];
int cnt[maxn],dep[maxn];
int nx[maxn][2];
priority_queue<pii,vector<pii>,greater<pii>> q[maxn];
void ins(){
    int p=0,len=strlen(s+1);
    for(int i=1;i<=len;i++){
        int &t=nx[p][s[i]-'0'];
        if(!t)  t=++tot,dep[t]=dep[p]+1;
        p=t;
    }
    cnt[p]++;
}
void dfs(int u){
    for(int o:{0,1}){
        int t=nx[u][o];
        if(t){
            dfs(t);
            if(q[u].size()<q[t].size()) q[u].swap(q[t]);
            while(!q[t].empty())    q[u].ep(q[t].top()),q[t].pop();
        }
        else    q[u].ep(dep[u]+1,0);
    }
    if(!nx[u][0]&&!nx[u][1]&&cnt[u]==1){
        while(!q[u].empty())q[u].pop();
        q[u].ep(dep[u]+2,1);cnt[u]--;
    }
    while(cnt[u]--){
        int w=q[u].top().fi,o=q[u].top().se;q[u].pop();
        // printf("%d %d %d\n",u,w,o);
        ans+=w-dep[u];
        if(o) q[u].ep(w+1,1),q[u].ep(w+1,1);
        else    q[u].ep(w+2,1);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        ins();
    }
    dfs(0);
    printf("%lld\n",ans);
}