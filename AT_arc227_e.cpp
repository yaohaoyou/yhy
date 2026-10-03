#include<bits/stdc++.h>
#include<tr2/dynamic_bitset>
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
const int maxn=4e5+10,mod=998244353;
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
unordered_map<int,unordered_map<int,int>> a;
tr2::dynamic_bitset<> dp;
bool mem2;
int main(){
    debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,c=1;scanf("%d",&x);
        while(x%2==0)   x>>=1,c<<=1;
        a[x][c]++;
    }
    int ans=1;
    for(auto [x,mp]:a){
        int c=1;while(x*c<n)c<<=1;
        dp.resize(c);dp.reset();
        // tr2::dynamic_bitset<> dp(c);
        dp.set(0);
        int tag=0,lst=1;
        for(int i=1;i<c;i<<=1){
            int w=mp[i]+tag;
            if(!w)  tag=0;
            else if(w&1) tag=w>>1,dp|=dp<<i;
            else    tag=(w>>1)-1,dp|=dp<<i,dp|=dp<<i;
        }
        // printf("%d %d\n",x,(dp&all).count());
        mmul(ans,dp.count());
    }
    printf("%d\n",ans);assert(ans);
}