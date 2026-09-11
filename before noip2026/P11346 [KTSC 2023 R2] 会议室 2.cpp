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
const int maxn=4010,mod=1e9+7;
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
pii a[maxn];
int f[maxn][maxn],g[maxn][maxn],h[maxn][maxn],s[maxn][maxn],w[maxn][maxn];
int fac[maxn],I[maxn],buc[maxn];
vector<int> vl[maxn],vr[maxn];
int solve(int L,int R,int n){
    buc[n]++;
    for(int i=L;i<=R;i++)for(int j=i;j<=R;j++){
        w[i][j]=w[i][j-1];
        for(int k:vr[j])w[i][j]+=k>=i;
    }
    for(int len=1;len<=R-L+1;len++){
        for(int l=L,r=l+len-1;r<=R;l++,r++){
            for(int i:vr[r])if(i>=l){
                if(i==l)    madd(f[l][r],imdel(imadd(s[l+1][r],s[l][r-1]),s[l+1][r-1]));
                else    madd(f[l][r],imdel(g[l][r-1],g[l][i-1]));
            }
            for(int i:vl[l])if(i<r) madd(f[l][r],imdel(h[l+1][r],h[i+1][r]));
            mmul(f[l][r],I[n-w[l][r]]);
            g[l][r]=imadd(g[l][r-1],f[l][r]);
            h[l][r]=imadd(h[l+1][r],f[l][r]);
            s[l][r]=imadd(imdel(imadd(s[l+1][r],s[l][r-1]),s[l+1][r-1]),f[l][r]);
        }
    }
    return immul(f[L][R],fac[n-1]);
}
int count_removals(vector<int> S,vector<int> E){
    int n=S.size();
    fac[0]=I[0]=1;for(int i=1;i<=n;i++)fac[i]=immul(fac[i-1],i),I[i]=qpow(i,mod-2);
    for(int i=1;i<=n;i++){
        a[i]=pii(S[i-1],E[i-1]);
        vl[a[i].fi].eb(a[i].se);vr[a[i].se].eb(a[i].fi);
        madd(f[a[i].fi][a[i].se],1);
    }
    sort(a+1,a+n+1);
    int ans=1;
    for(int i=2,l=1,r=a[1].se,j=1;i<=n;i++){
        if(a[i].fi<=r)  gmx(r,a[i].se);
        else    mmul(ans,solve(l,r,i-j)),j=i,l=r+1,r=a[i].se;
        if(i==n)    mmul(ans,solve(l,r,i-j+1));
    }
    for(int i=1;i<=n;i++)   mmul(ans,fac[buc[i]]);
    return ans;
}