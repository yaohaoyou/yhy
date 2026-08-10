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
using namespace std;
const int maxn=1e5+10;
int n,k;
string a;
vector<pair<int,string>> vec;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
void dfs(int x){
    if(x>n){
        vector<piii> E;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                int k=0;while(j+k<=n&&a[i+k-1]==a[j+k-1])k++;
                E.eb(k,pii(i,j));
            }
        }
        sort(E.begin(),E.end(),greater<piii>());
        int sum=0;
        U.init();
        for(auto [i,j]:E){
            int u=j.fi,v=j.se;
            u=U.find(u);v=U.find(v);
            if(u==v)    continue;
            sum+=i;
            U.merge(u,v);
        }
        // cout<<sum<<' '<<a<<'\n';
        vec.eb(sum,a);
        return;
    }
    for(char c='a';c<='z';c++){
        a[x-1]=c;
        dfs(x+1);
    }
}
void matt(){
    vec.clear();
    scanf("%d%d",&n,&k);
    if(n<=4){
        a.resize(n);
        dfs(1);
        nth_element(vec.begin(),vec.begin()+k-1,vec.end());
        cout<<vec[k-1].fi<<'\n'<<vec[k-1].se<<'\n';
    }
    else{
        int N=n;n=4;
        a.resize(n);
        dfs(1);
        nth_element(vec.begin(),vec.begin()+k-1,vec.end());
        string ans="";
        n=N;
        ll sum=vec[k-1].fi;
        for(int i=1;i<=n-4;i++) ans+=vec[k-1].se[0];
        ans+=vec[k-1].se;
        int now=0;
        for(int i=n-3;i<=n;i++){
            int k=0;while(i+k<=n&&ans[i+k-1]==ans[n-4+k-1])k++;
            now=max(now,k);
        }
        for(int i=n-4;i;i--)    sum+=now,now++;
        cout<<sum<<'\n'<<ans<<'\n';
    }
}
int main(){int T;scanf("%d",&T);while(T--)matt();}