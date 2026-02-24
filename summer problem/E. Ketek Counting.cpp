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
const int maxn=3e4+10,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
char a[maxn],b[maxn];
int f[maxn],dp[maxn],suf[maxn];
int main(){
    scanf("%s",a+1);n=strlen(a+1);
    {int m=0;for(int i=1,j=n;i<=j;i++,j--)b[++m]=a[i],b[++m]=a[j];}
    // for(int i=1;i<=n;i++)printf("%c",b[i]);puts("");
    for(int i=n;i;i--)  suf[i]=suf[i+1]+(b[i]=='?');
    dp[0]=1;
    for(int i=1;i<=n;i++){
        int l=i,r=i+1;
        f[r-1]=1;
        while(l>0&&r<=n){
            if(b[l]!='?'&&b[r]!='?'){
                if(b[l]==b[r])  f[r]=f[r-1];
                else    break;
            }
            else if(b[l]=='?'&&b[r]=='?')   f[r]=immul(f[r-1],26);
            else f[r]=f[r-1];
            // printf("%d %d : %d\n",l,r,f[r]);
            madd(dp[r],immul(dp[l-1],f[r]));
            l--;r++;
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++)   madd(ans,immul(dp[i],qpow(26,suf[i+1])));
    printf("%d\n",ans);
}