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
const int maxn=2e6+10;
const uint32_t MOD = 2147483647;
struct ModInt {
    uint32_t x;
    ModInt(uint32_t x = 0) : x(x % MOD) {
        if (x >= MOD) x -= MOD;
    }
    ModInt& operator+=(ModInt rhs) {
        x += rhs.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }
    ModInt& operator-=(ModInt rhs) {
        if (x < rhs.x) x += MOD;
        x -= rhs.x;
        return *this;
    }
    ModInt& operator*=(ModInt rhs) {
        uint64_t product = (uint64_t)x * rhs.x;
        uint32_t low = product & 0x7FFFFFFF;
        uint32_t high = product >> 31;
        x = low + high;
        if (x >= MOD) x -= MOD;
        return *this;
    }
    ModInt operator+(ModInt rhs) const { return ModInt(*this) += rhs; }
    ModInt operator-(ModInt rhs) const { return ModInt(*this) -= rhs; }
    ModInt operator*(ModInt rhs) const { return ModInt(*this) *= rhs; }
    operator int() const { return (int)x; }
    ModInt pow(int64_t e) const {
        ModInt res(1), base(*this);
        while (e) {
            if (e & 1) res *= base;
            base *= base;
            e >>= 1;
        }
        return res;
    }
    
    // 需要逆元时用费马小定理
    ModInt inv() const { return pow(MOD - 2); }
    
    ModInt& operator/=(ModInt rhs) { return *this *= rhs.inv(); }
    ModInt operator/(ModInt rhs) const { return ModInt(*this) /= rhs; }
    
    explicit operator uint32_t() const { return x; }
};
using mint = ModInt;
int n;
char a[maxn];
int buc[10];
mint f[2][maxn/2][11],fac[maxn];
mint solve(){
    for(int i=0;i<2;i++)for(int j=0;j<maxn/2;j++)for(int k=0;k<11;k++)f[i][j][k]=0;
    int X=n>>1,Y=n-X;
    int s=0;for(int i=1;i<10;i++)(s+=1ll*buc[i]*i%11)%=11;
    if(count(buc,buc+10,0)==9)  return !(n&1);
    bool o=0;f[!o][0][0]=mint(1);
    for(int i=0;i<10;i++,o^=1){
        for(int j=0;j<=Y;j++)for(int k=0;k<11;k++)f[o][j][k]=0;
        for(int j=0;j<=Y;j++){
            for(int k=0;k<11;k++){
                for(int x=0;x<=j&&x<=buc[i];x++)f[o][j][k]+=f[!o][j-x][(k-x*i%11+11)%11]/fac[x]/fac[buc[i]-x];
            }
        }
    }
    o^=1;
    if(s&1) s=(s+11)/2;
    else s>>=1;
    return f[o][X][s]*fac[X]*fac[Y];
}
int main(){
    scanf("%s",a+1);n=strlen(a+1);
    fac[0]=mint(1);for(int i=1;i<=n;i++)fac[i]=fac[i-1]*mint(i);
    for(int i=1;i<=n;i++)   buc[a[i]-'0']++;
    mint x=solve();
    if(buc[0]){
        n--;buc[0]--;
        x-=solve();
    }
    printf("%d\n",int(x));
}