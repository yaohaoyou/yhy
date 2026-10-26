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
const int maxn=5010,mod=998244353;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
bool mem1;
int n;
int a[maxn];
mit f[maxn][maxn],s[maxn];
mit dp(int l,int r){
    debug("%d %d\n",l,r);
    vector<int> v;
    mit res=1;
    for(int i=r;i>=l;i--){
        if(a[i]==-1)    v.eb(0);
        else{res*=dp(a[i]+1,i-1);i=a[i]+1;v.eb(1);}
    }
    reverse(v.begin(),v.end());
    f[0][1]=1;
    for(int i=1;i<=v.size();i++){
        s[0]=f[i-1][0];for(int j=1;j<=i;j++)s[j]=s[j-1]+f[i-1][j];
        if(!v[i-1]){
            for(int j=2;j<=i+1;j++) f[i][j]=s[i]-s[j-2];
        }
        else{
            for(int j=2;j<=i+1;j++)f[i][j]=f[i-1][j-1];
        }
    }
    res*=accumulate(f[v.size()],f[v.size()]+v.size()+2,mit(0));
    return res;
}
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        if(!~a[i])continue;
        if(a[i]>=i) return puts("0"),void();
        for(int j=a[i]+1;j<i;j++)if((~a[j])&&a[j]<a[i])return puts("0"),void();
    }
    printf("%d\n",dp(1,n));
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}