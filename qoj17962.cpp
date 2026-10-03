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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=50;
int n;ll k,ans;
int a[maxn][maxn];
unordered_map<ll,ll> mp[maxn][maxn];
map<ll,ll> m[2][maxn][maxn],tmp;
bool mem2;
void dfs1(int x,int y,int stp,ll s,bool o){
    if(s>k) return;
    o|=(s==k);
    if(!stp){
        mp[x][y][s]++;
        m[o][x][y][s]++;
        return;
    }
    dfs1(x+1,y,stp-1,a[x+1][y]+max(0ll,s),o);
    dfs1(x,y+1,stp-1,a[x][y+1]+max(0ll,s),o);
}
void dfs2(int x,int y,int stp,ll s,bool o){
    if(s>k) return;
    o|=(s==k);
    if(!stp){
        if(mp[x-1][y].count(k-s))   ans+=mp[x-1][y][k-s];
        if(mp[x][y-1].count(k-s))   ans+=mp[x][y-1][k-s];
        for(auto [xx,yy]:{pii(x-1,y),pii(x,y-1)}){
            auto it=m[1][xx][yy].lower_bound(k-s);
            if(it!=m[1][xx][yy].begin()){it--;ans+=it->se;}
            if(o){
                it=m[0][xx][yy].lower_bound(k-s);
                if(it!=m[0][xx][yy].begin()){it--;ans+=it->se;}
            }
        }
        // printf("%d %d : %d\n",x,y,ans);
        return;
    }
    dfs2(x-1,y,stp-1,a[x-1][y]+max(0ll,s),o);
    dfs2(x,y-1,stp-1,a[x][y-1]+max(0ll,s),o);
}
int main(){
    debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
    if(n==1)    return printf("%d\n",a[1][1]==k),0;
    dfs1(1,1,n-1,a[1][1],0);
    for(int x=1;x<=n;x++){
        int y=n+1-x;
        tmp.swap(m[0][x][y]);m[0][x][y].clear();
        ll s=0;for(auto [i,j]:tmp) m[0][x][y][i]=(s+=j);
        s=0;tmp.swap(m[1][x][y]);m[1][x][y].clear();
        for(auto [i,j]:tmp) m[1][x][y][i]=(s+=j);
    }
    dfs2(n,n,n-2,a[n][n],0);
    printf("%lld\n",ans);
}