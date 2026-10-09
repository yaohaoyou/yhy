#include<bits/stdc++.h>
#define ll long long
#define LL __int128
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
const int maxn=5e5+10,lgV=80,mod=998244353;
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
int n;
ll a[maxn];
int f[lgV+1][maxn],s[lgV+1][maxn];
LL pq[lgV+11];
deque<int> q;
bool mem2;
int main(){
    // freopen("c.in","r",stdin);freopen("c.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    for(int i=0;i<=lgV+10;i++) pq[i]=(LL)(1)<<i;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        for(int j=0;j<=lgV;j++) s[j][i]=s[j][i-1];
        for(int j=0;j<=lgV;j++)if(a[i]<pq[j])madd(s[j][i],a[i]%mod);
    }
    for(int i=0;i<=lgV;i++)for(int j=1;j<=n;j++)madd(s[i][j],s[i][j-1]);
    for(int i=0;i<=lgV;i++){
        f[i][n+1]=n+1;
        q.clear();
        LL S=1;
        for(int r=n,l=n+1;r;r--){
            int nl=min(f[i][r+1],i?f[i-1][r]:r+1);
            while(!q.empty()&&q.front()>r)  q.pop_front();
            while(l>nl){
                l--;
                if(a[l]<pq[i])  S+=a[l];
                if(a[l]<pq[i+1]&&a[l]>=pq[i]){
                    while(!q.empty()&&a[q.back()]>=a[l])    q.pop_back();
                    q.eb(l);
                }
            }
            LL mn=q.empty()?pq[i+1]:a[q.front()];
            if(S>=mn){f[i][r]=l;if(a[r]<pq[i])S-=a[r];continue;}
            while(l){
                l--;
                if(a[l]<pq[i])  S+=a[l];
                if(a[l]<pq[i+1]&&a[l]>=pq[i]){
                    while(!q.empty()&&a[q.back()]>=a[l])    q.pop_back();
                    q.eb(l);
                }
                LL mn=q.empty()?pq[i+1]:a[q.front()];
                if(S>=mn)   break;
                else if(l==1){l=0;break;}
            }
            f[i][r]=l;
            if(a[r]<pq[i])  S-=a[r];
        }
    }
    int ans=0;
    for(int r=1;r<=n;r++){
        for(int i=0;i<lgV;i++){
            int L=f[i+1][r]+1,R=f[i][r];
            if(L>R) continue;
            madd(ans,immul(imdel(s[i+1][r],s[i+1][r-1]),R-L+1));
            mdel(ans,imdel(s[i+1][R-1],(L>1?s[i+1][L-2]:0)));
        }
    }
    madd(ans,1ull*n*(n+1)/2%mod);
    printf("%d\n",ans);
}