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
const int maxn=5e5+10,B=19;
bool mem1;
int n;
int a[maxn],b[maxn],id[maxn],bl[maxn],br[maxn];
int f[B][maxn],g[B][maxn],h[B][maxn];
int Log[maxn];
struct ST{
    int st[B][maxn/B+10],a[maxn],pre[maxn],suf[maxn];
    void build(auto &arr){
        memc(a,arr);
        for(int i=1;i<=id[n];i++){
            int l=bl[i],r=br[i];
            pre[l]=a[l];for(int j=l+1;j<=r;j++) pre[j]=max(pre[j-1],a[j]);
            suf[r]=a[r];for(int j=r-1;j>=l;j--) suf[j]=max(suf[j+1],a[j]);
            st[0][i]=pre[r];
        }
        for(int i=1;i<=Log[id[n]];i++)
            for(int j=1;j+(1<<i)-1<=id[n];j++)
                st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int query(int l,int r){
        if(l>r)return 0;
        if(id[r]-id[l]>1){
            int k=Log[id[r]-id[l]-1];
            return max({suf[l],st[k][id[l]+1],st[k][id[r]-(1<<k)],pre[r]});
        }
        else if(id[l]^id[r])    return max(suf[l],pre[r]);
        else    return *max_element(a+l,a+r+1);
    }
}F[B],G[B],H[B];
bool mem2;
vector<int> solve(vector<int> &v,vector<int> &w,vector<pii> &queries){
    n=v.size();
    for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
    for(int i=1;i<=n;i++)   a[i]=min(v[i-1]+i,n);
    for(int i=1;i<=n;i++)   b[i]=min(w[i-1]+i,n);
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,n);
    for(int i=1;i<=n;i++)   f[0][i]=a[i],g[0][i]=b[i],h[0][i]=i;
    F[0].build(f[0]);G[0].build(g[0]);H[0].build(h[0]);
    for(int i=1;i<=Log[n];i++){
        for(int j=1;j<=n;j++){
            f[i][j]=max(G[i-1].query(j,h[i-1][j]),F[i-1].query(j,f[i-1][j]));
            g[i][j]=max(G[i-1].query(j,f[i-1][j]),F[i-1].query(j,g[i-1][j]));
            h[i][j]=max(H[i-1].query(j,f[i-1][j]),F[i-1].query(j,h[i-1][j]));
        }
        F[i].build(f[i]);G[i].build(g[i]);H[i].build(h[i]);
    }
    int q=queries.size();
    vector<int> out;
    for(int i=0;i<q;i++){
        int L=queries[i].fi,l1,l2,r=queries[i].se;L++;r++;l1=L;l2=0;
        if(L==r){out.eb(0);continue;}
        int ans=0;
        for(int i=Log[n];~i;i--){
            int to=max(F[i].query(L,l1),G[i].query(L,l2));
            if(to<r){
                ans|=(1<<i),l2=max(F[i].query(L,l2),H[i].query(L,l1)),l1=to;
            }
        }
        out.eb(ans+1);
    }
    return out;
}
// int main() {
//     debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     int n;
//     cin >> n;
//     vector<int> v(n);
//     for (int i = 0; i < n; i++) {
//         cin >> v[i];
//     }
//     vector<int> w(n);
//     for (int i = 0; i < n; i++) {
//         cin >> w[i];
//     }
//     int m;
//     cin >> m;
//     vector<pair<int, int>> queries(m);
//     for (int i = 0; i < m; i++) {
//         cin >> queries[i].first >> queries[i].second;
//     }
//     vector<int> results = solve(v, w, queries);
//     for (int i = 0; i < m; i++) {
//         cout << results[i] << "\n";
//     }
//     return 0;
// }