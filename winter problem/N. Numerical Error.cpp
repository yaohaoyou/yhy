#include<set>
#include<map>
#include<queue>
#include<ctime>
#include<cstdio>
#include<vector>
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
#define piii pair<pii,int>
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
const int N=1e5+10,M=3.4e7+10,mod=998244353;db eps=1e-5,ee=1e-10;
int n;
db a[N];
namespace N23{
    vector<pair<db,int>> vt[100];
    db f[1<<24];
    void solve(){
        debug("solve n<=23");
        rep(s,1,(1<<n)-1){
            int x=__builtin_ctz(s&-s);
            f[s]=f[s^(1<<x)]+(db)1/a[x+1];
            vt[pc(s)].eb(f[s],s);
        }
        rep(i,1,n-1){
            sort(rg(vt[i]));
            rep(j,0,(int)vt[i].size()-2)
                if(vt[i][j+1].fi-vt[i][j].fi<=eps){
                    puts("Yes");
                    printf("%d\n",i);
                    rep(k,0,n-1)if(vt[i][j].se>>k&1) printf("%d ",k+1);
                    puts("");
                    rep(k,0,n-1)if(vt[i][j+1].se>>k&1) printf("%d ",k+1);
                    exit(0);
                }
        }
        puts("No");
        exit(0);
    }
}
// inline pii find2(db x,bool f){if(f){rep(i,1,n)rep(j,i+1,n)if(a[i]+a[j]==x)return pii(i,j);}else{per(i,n,1)per(j,n,i+1)if(a[i]+a[j]==x)return pii(i,j);}}
// inline piii find3(db x,bool f){
//     if(f){rep(i,1,n)rep(j,i+1,n)rep(k,j+1,n)if(a[i]+a[j]+a[k]==x)return piii(pii(i,j),k);}
//     else{per(i,n,1)per(j,n,i+1)per(k,n,j+1)if(a[i]+a[j]+a[k]==x)return piii(pii(i,j),k);}
// }
db f[M];int len;
int ch[N];bool vis[N];
bool find(int x,int lst,int y,db sum,db nd){
    if(sum>nd)  return false;
    if(x>y){
        if(abs(sum-nd)<=ee) return true;
        return false;
    }
    for(int i=lst+1;i<=n;i++){
        if(vis[i])  continue;
        ch[x]=i;
        if(find(x+1,i,y,sum+a[i],nd))return true;
    }
    return false;
}
void dfs(int x,int lst,int y,db sum){
    if(x>y) return f[++len]=sum,void();
    for(int i=lst+1;i<=n;i++)   dfs(x+1,i,y,sum+a[i]);
}
inline bool chk(int x){ll s=1;for(int i=1;i<=x;i++)s*=n-i+1;return s<=M;}
void misaka(int _ID){
    n=read();
    rep(i,1,n)  a[i]=read();
    rep(i,1,n)rep(j,i+1,n)if(a[i]==a[j]){
        puts("Yes");
        printf("1\n%d\n%d\n",i,j);
        return;
    }
    if(n<=23)   N23::solve();
    rep(i,1,n)a[i]=(db)1/a[i];
    int sz=1;
    while(sz<=n&&chk(sz)){
        // debug("sz = %d\n",sz);
        len=0;dfs(1,0,sz,0);sort(f+1,f+len+1);
        rep(i,2,len)if(f[i]-f[i-1]<=eps){
            puts("Yes");
            assert(find(1,0,sz,0,f[i]));
            printf("%d\n",sz);rep(j,1,sz)printf("%d ",ch[j]),vis[ch[j]]=true;puts("");
            find(1,0,sz,0,f[i-1]);rep(j,1,sz)printf("%d ",ch[j]),vis[ch[j]]=true;puts("");
            return;
        }
        sz++;
    }
    puts("No");
    // assert(n<=586);
    // rep(i,1,n)rep(j,i+1,n)f[++len]=a[i]+a[j];
    // sort(f+1,f+len+1);
    // rep(i,2,len)if(f[i]-f[i-1]<=eps){
    //     puts("Yes");pii x=find2(f[i],1),y=find2(f[i-1],0);
    //     printf("2\n%d %d\n%d %d\n",x.fi,x.se,y.fi,y.se);
    //     return;
    // }
    // len=0;
    // rep(i,1,n)rep(j,i+1,n)rep(k,j+1,n)f[++len]=a[i]+a[j]+a[k];
    // sort(f+1,f+len+1);
    // rep(i,2,len)if(f[i]-f[i-1]<=eps){
    //     puts("Yes");piii x=find3(f[i],1),y=find3(f[i-1],0);
    //     printf("3\n%d %d %d\n%d %d %d\n",x.fi.fi,x.fi.se,x.se,y.fi.fi,y.fi.se,y.se);
    //     return;
    // }
    // puts("No");
}
bool __ed;
signed main(){
    // #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    // #endif
    
    int T=1;
    rep(i,1,T) misaka(i);
    return 0;
}
