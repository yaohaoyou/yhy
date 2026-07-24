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
const int maxn=1e5+10,mod=998244353;
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
int n,k;
void ntt(vector<int> &a, bool f) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = qpow(3, (mod - 1) / len);
        if (f) wlen = qpow(wlen, mod - 2);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; ++j) {
                int u = a[i + j], v = 1LL * a[i + j + len / 2] * w % mod;
                a[i + j] = (u + v) % mod;
                a[i + j + len / 2] = (u - v + mod) % mod;
                w = 1LL * w * wlen % mod;
            }
        }
    }
    if (f) { int inv = qpow(n, mod - 2); for (int i = 0; i < n; ++i) a[i] = 1LL * a[i] * inv % mod; }
}

vector<int> mul(vector<int> a, vector<int> b) {
    int n = 1, m = a.size() + b.size() - 1;
    while (n < m) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, 0); ntt(b, 0);
    for (int i = 0; i < n; ++i) a[i] = 1LL * a[i] * b[i] % mod;
    ntt(a, 1); a.resize(m);
    return a;
}

vector<int> S2_row(int n) {
    vector<int> fac(n + 1), ifac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = 1LL * fac[i - 1] * i % mod;
    ifac[n] = qpow(fac[n], mod - 2);
    for (int i = n; i >= 1; --i) ifac[i - 1] = 1LL * ifac[i] * i % mod;
    vector<int> A(n + 1), B(n + 1);
    for (int i = 0; i <= n; ++i) {
        A[i] = 1LL * qpow(i, n) * ifac[i] % mod;
        B[i] = (i & 1) ? mod - ifac[i] : ifac[i];
    }
    vector<int> S = mul(A, B);
    S.resize(n + 1);
    return S;
}
int main(){
    scanf("%d%d",&n,&k);
    vector<int> stir=S2_row(k);
    int A=1,ans=0;
    for(int i=0;i<=k&&i<=n;i++){
        if(i)   mmul(A,n-i+1);
        madd(ans,1ull*A*stir[i]%mod*qpow(n+1,n-i)%mod);
    }
    printf("%d\n",ans);
}