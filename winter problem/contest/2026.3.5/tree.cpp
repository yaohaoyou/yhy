#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
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
const int maxn=1e4+10,mod=998244353;
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
int a[maxn],f[maxn][2],s[maxn][2];
bool b[maxn];
int main(){
    freopen("tree.in","r",stdin);freopen("tree.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);n=unique(a+1,a+n+1)-a-1;
    int V=*max_element(a+1,a+n+1);
    for(int i=1;i<=n;i++)   b[a[i]]=true;
    int ans=0;
    for(int k=0;k<=V;k++){
        mems(f,0);mems(s,0);
        f[max(1,k)][!k]=s[max(1,k)][!k]=1;
        for(int i=max(1,k)+1;i<=V;i++){
            if(!b[i]){
                f[i][0]=f[i-1][0];
                f[i][1]=f[i-1][1];
            }
            else{
                f[i][1]=imdel(s[i-1][1],s[max(i-k,max(1,k)+1)-2][1]);
                if(i-k>=max(1,k)+1){f[i][0]=imdel(s[i-1][0],s[i-k-1][0]);madd(f[i][1],f[i-k-1][0]);}
                else    f[i][0]=imdel(s[i-1][0],s[max(1,k)-1][0]);
                // for(int j=i;j>=i-k&&j>max(1,k);j--){
                //     madd(f[i][j==i-k],f[j-1][0]);
                //     madd(f[i][1],f[j-1][1]);
                // }
            }
            // printf("%d ",f[i][1]);
            s[i][0]=imadd(s[i-1][0],f[i][0]);
            s[i][1]=imadd(s[i-1][1],f[i][1]);
        }
        madd(ans,f[V][1]);
        if(b[k])    madd(ans,f[V][0]);
        // printf("%d\n",ans);
    }
    printf("%d\n",ans);
}