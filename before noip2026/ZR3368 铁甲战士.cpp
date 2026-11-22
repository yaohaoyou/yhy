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
int n,m;
int a[maxn],b[maxn];
ll f[maxn],g[maxn];
vector<int> v[maxn];
inline int pr(int x){
    int k=lower_bound(v[a[x]].begin(),v[a[x]].end(),x)-v[a[x]].begin();
    if(k>0) return k-1;
    return v[a[x]].size()-1;
}
inline int nx(int x){
    int k=lower_bound(v[a[x]].begin(),v[a[x]].end(),x)-v[a[x]].begin();
    if(k+1<v[a[x]].size()) return k+1;
    return 0;
}
void discrete(){
    memc(b,a);sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+m+1,a[i])-b;
}
inline int dis(int x,int y){if(x>y)swap(x,y);return min(y-x,n-(y-x));}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    discrete();
    for(int i=1;i<=n;i++)   v[a[i]].eb(i);
    mems(g,0x3f);mems(f,0x3f);
    for(int i:v[1]) f[i]=min(n+1-i,i-1);
    for(int i=1;i<=m;i++){
        int T=3;
        while(T--){
            for(int j=1;j<v[i].size();j++)  gmn(f[v[i][j]],f[v[i][j-1]]+dis(v[i][j],v[i][j-1]));
            gmn(f[v[i][0]],f[v[i].back()]+dis(v[i][0],v[i].back()));
            for(int j=int(v[i].size())-2;~j;j--) gmn(f[v[i][j]],f[v[i][j+1]]+dis(v[i][j+1],v[i][j]));
            gmn(f[v[i].back()],f[v[i][0]]+dis(v[i][0],v[i].back()));
        }
        if(v[i].size()>1){
            for(int j:v[i]){
                int k=v[i][pr(j)];
                if(k<j) gmn(g[k],f[j]+n-(j-k));
                else    gmn(g[k],f[j]+k-j);
                k=v[i][nx(j)];
                if(k>j) gmn(g[k],f[j]+n-(k-j));
                else    gmn(g[k],f[j]+j-k);
            }
        }
        else    g[v[i][0]]=f[v[i][0]];
        T=3;
        while(T--){
            for(int j=1;j<v[i].size();j++)  gmn(g[v[i][j]],g[v[i][j-1]]+dis(v[i][j],v[i][j-1]));
            gmn(g[v[i][0]],g[v[i].back()]+dis(v[i][0],v[i].back()));
            for(int j=int(v[i].size())-2;~j;j--) gmn(g[v[i][j]],g[v[i][j+1]]+dis(v[i][j+1],v[i][j]));
            gmn(g[v[i].back()],g[v[i][0]]+dis(v[i][0],v[i].back()));
        }
        if(i==m)    break;
        for(int j:v[i]){
            int k=lower_bound(v[i+1].begin(),v[i+1].end(),j)-v[i+1].begin();
            if(k==v[i+1].size())k=0;
            k=v[i+1][k];
            if(k>j) gmn(f[k],g[j]+k-j);
            else    gmn(f[k],g[j]+n-(j-k));
            k=upper_bound(v[i+1].begin(),v[i+1].end(),j)-v[i+1].begin()-1;
            if(k<0) k=v[i+1].size()-1;
            k=v[i+1][k];
            if(k<j) gmn(f[k],g[j]+j-k);
            else    gmn(f[k],g[j]+n-(k-j));
            // printf("g[%d] = %d\n",j,g[j]);
        }
        // gmn(g[v[i][0]],g[v[i].back()]+n-(v[i].back()-v[i][0]));
        // for(int j=1;j<v[i].size();j++)  assert(g[v[i][j]]-g[v[i][j-1]]<=v[i][j]-v[i][j-1]);
    }
    ll ans=1e18;for(int i:v[m])gmn(ans,g[i]);
    printf("%lld\n",ans);
}