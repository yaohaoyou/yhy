#include<set>
#include<map>
#include<queue>
#include<ctime>
#include<cstdio>
#include<vector>
#include<bitset>
#include<random>
#include<cassert>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
#define ep emplace
#define ll long long
#define db long double
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char ch=getchar();int f=1,x=0;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=1e5+10,mod=998244353;
int n=8,p[N];db a[N],b[N],c[5][N],ans;
void misaka(int _ID){
    rep(i,1,n) a[i]=read(),b[i]=read(),p[i]=i;
    do{
        rep(i,1,n) c[0][i]=1;
        rep(j,1,3)rep(i,1,n) c[j][i]=0;
        for(int l=1,x=1;l<n;l<<=1,x++){
            for(int i=1;i<n;i+=l<<1){
                int m=i+l-1,r=i+(l<<1)-1;
                rep(j,i,m){
                    rep(k,m+1,r){
                        db h=a[p[j]],y=b[p[k]];
                        c[x][j]+=c[x-1][j]*c[x-1][k]*h/(h+y);
                    }
                }
                rep(j,m+1,r){
                    rep(k,i,m){
                        db h=b[p[j]],y=a[p[k]];
                        c[x][j]+=c[x-1][j]*c[x-1][k]*h/(h+y);
                    }
                }
            }
        }
        ans=max(ans,c[3][1]);
    }while(next_permutation(p+1,p+n+1));
    printf("%.10Lf",ans);
}
bool __ed;
signed main(){
    int T=1;
    rep(i,1,T) misaka(i);
    return 0;
}

