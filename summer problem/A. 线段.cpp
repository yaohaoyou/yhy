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
// #include "segment.h"

void init(int c,int t){return;}
const int maxn=3010,maxm=1010,maxk=210,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m;
pii a[maxn];
int f[2][maxm][maxm][2];
vector<int> v[maxn],vr[maxn];
vector<int> segment(int N,int M,int K,vector<int> L,vector<int> R){
    mems(f,0);
    n=N;m=M;
    for(int i=1;i<=n;i++){
        a[i]=pii(L[i-1],R[i-1]);
        v[a[i].fi].eb(a[i].se);
        f[1][a[i].fi][a[i].se][1]++;
    }
    vector<int> res(K+1,0);
    for(int k=1;k<=K;k++){
        mems(f[(k+1)&1],0);
        if(k==2){
            for(int i=1;i<=m;i++)
                for(int j=0;j<v[i].size();j++)
                    for(int k=j+1;k<v[i].size();k++)    f[0][min(v[i][j],v[i][k])][max(v[i][j],v[i][k])][1]++;
        }
        for(int i=0;i<=m;i++){
            for(int j=i+1;j<=m;j++){
                int w=imadd(f[k&1][i][j][0],f[k&1][i][j][1]);
                if(w)madd(f[k&1][i+1][j][0],w);
            }
            for(int j=i+1;j<=m;j++){
                int w=imadd(f[k&1][i][j][0],f[k&1][i][j][1]);if(!w)continue;
                for(int x:v[i+1])
                    madd(f[(k+1)&1][min(j,x)][max(j,x)][1],w);
            }
        }
        for(int i=0;i<=m;i++)for(int j=i;j<=m;j++)madd(res[k],f[k&1][i][j][1]);
    }
    for(int i=1;i<=m;i++)   v[i].clear();
    return res;
}

signed main() {
    int c, t;
    std::cin >> c >> t;
    init(c, t);
    for (int _ = 0; _ < t; _++) {
        int n, m, k;
        std::cin >> n >> m >> k;

        std::vector<int> l(n), r(n);
        for (int i = 0; i < n; i++) {
            std::cin >> l[i] >> r[i];
        }

        std::vector<int> a = segment(n, m, k, l, r);

        if (static_cast<int>(a.size()) != k + 1) {
            std::cout << "The length of a is not k + 1.\n";
            continue;
        }

        for (int i = 1; i <= k; i++) {
            std::cout << a[i] << " \n"[i == k];
        }
    }
    return 0;
}
