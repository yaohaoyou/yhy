#pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define if(sth) if(__builtin_expect(sth,1))
#define while(sth) while(__builtin_expect(sth,1))
using namespace std;
const int maxn=3e5+10,B=800;
bool mem1;
int n,m,tot;
ll ans;
int a[maxn];
int ord[maxn],bac[B];
vector<int> v[B];
unordered_map<int,int> cnt;
unordered_set<ull> st;
void init(){
    for(int i=1;i<=tot;i++)v[i].clear();
    tot=ans=0;
    for(int i=1;i<=n;i++)ord[i]=0;
    st.clear();
    cnt.clear();
}
inline ull Hash(ull x,ull y){return (x<<13)^(y>>1)^(y<<17)^(x<<3);}
bool mem2;
void solve(){
    // printf("%.2f MB",abs(&mem1-&mem2)/1024.0/1024.0);
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        cnt[a[i]]++;
        st.ep(Hash(a[i],a[i]));
    }
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        st.ep(Hash(x,y));st.ep(Hash(y,x));
    }
    for(auto [i,j]:cnt){
        if(!ord[j])  ord[j]=++tot,bac[tot]=j;
        v[ord[j]].eb(i);
    }
    // if(a[1]==476508496) printf("tot = %d\n",tot),exit(0);
    for(int i=1;i<=tot;i++) sort(v[i].begin(),v[i].end());
    for(int i=1;i<=n;i++){
        if(!cnt[a[i]])  continue;
        int x=a[i],cx=cnt[a[i]];
        cnt[a[i]]=0;
        int j=tot+1;
        while(--j){
            int l=v[j].size();
            while(~--l){
                int y=v[j][l],cy=bac[j];
                if(1ll*(x+y)*(cx+cy)<=ans)  break;
                if(st.find(Hash(x,y))!=st.end())    continue;
                ans=max(ans,1ll*(x+y)*(cx+cy));
                break;
            }
        }
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)solve();}