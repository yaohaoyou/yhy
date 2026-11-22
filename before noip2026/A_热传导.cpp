#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define ep emplace
#define eb emplace_back
#define pii pair<int,int>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
namespace OIMATT{
    const int maxn=2e5+10;
    int n;ll ans;
    int a[maxn],b[maxn],A[maxn],B[maxn],s[maxn],f[maxn],sf[maxn],pr[maxn][2];
    inline int calc(int l,int r){return (r-l+1)*2-(s[r]-s[l-1]);}
    bool chk(){
        for(int i=1,j=n;i<j;i++,j--)if(a[i]^a[j])return 0;
        return 1;
    }
    ll solve(){
        for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i]+b[i];
        vector<int> v;v.eb(0);
        for(int i=1;i<=n;i++)if(a[i]&&b[i])v.eb(i);
        v.eb(n+1);a[n+1]=b[n+1]=0;
        for(int i=1;i<=n;i++){
            pr[i][0]=pr[i-1][0];pr[i][1]=pr[i-1][1];
            if(a[i])    pr[i][0]=i;
            if(b[i])    pr[i][1]=i;
        }
        fll(f,1e9,n+5);
        ll res=0;
        for(int i=0;i+1<v.size();i++){
            int l=v[i]+1,r=v[i+1]-1;
            if(a[r+1])r++;
            f[l-1]=0;sf[l-1]=1e9;
            for(int i=l;i<=r;i++){
                sf[i]=min(sf[i-1],f[i-1]-i*2+s[i-1]);
                if(!a[i]&&!b[i])    f[i]=f[i-1];
                if(a[l-1]&&b[l-1])  gmn(f[i],calc(l-1,i));
                int j=min(pr[i][0],pr[i][1]);
                if(j>=l)    gmn(f[i],sf[j]+(i+1)*2-s[i]);
                // for(int j=i;j>=l;j--){
                    // fa|=a[j];fb|=b[j];
                    // if(fa&&fb){
                        // gmn(f[i],f[j-1]-j*2+s[j-1]+(i+1)*2-s[i]);
                        // gmn(f[i],sf[j]+(i+1)*2-s[i]);
                        // break;
                    // }
                // }
            }
            res+=f[r];
            // printf("[%d,%d] %d\n",l,r,calc(5,r));
            // for(int i=l;i<=r;i++)   printf("f[%d] = %d\n",i,f[i]);
        }
        return res;
    }
    void matt(int _c){
        scanf("%d",&n);const int N=n;
        for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
        if(chk()) return puts("0"),void();
        cpy(b,a,n);
        reverse(b+1,b+n+1);
        n>>=1;
        if(a[n+1])  b[++n]=1;
        cpy(A,a,n);cpy(B,b,n);
        ans=solve();
        if(count(a+1,a+n+1,1)){
            int nn=n,w=0;
            for(int i=n;i;i--)if(a[i])break;
            else    a[i]=1,w++;
            w++;
            if(N&1) b[++n]=1,a[n]=1;
            else    b[n]=1;
            gmn(ans,solve()+w);
            n=nn;cpy(a,A,n);cpy(b,B,n);
        }
        if(count(b+1,b+n+1,1)){
            int nn=n,w=0;
            for(int i=n;i;i--)if(b[i])break;
            else    b[i]=1,w++;
            w++;
            if(N&1) a[++n]=1,b[n]=1;
            else    a[n]=1;
            gmn(ans,solve()+w);
            n=nn;cpy(a,A,n);cpy(b,B,n);
        }
        printf("%lld\n",ans);
    }
}
bool mem2;
int main(){
    // debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T=1;scanf("%d",&T);for(int i=1;i<=T;i++)OIMATT::matt(i);
    return 0;
}