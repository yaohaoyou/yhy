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
const int maxn=1e6+10,mod=998244353;
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
// #define NO return puts("0"),0
inline void NO(){
    puts("0");
    exit(0);
}
int n;
int a[maxn],b[maxn],s[2][maxn];
queue<int> q[2];
void baoli(){
    iota(b+1,b+n+1,1);
    int ans=0;
    do{
        bool flag=true;
        for(int i=1;i<=n;i++)if(a[b[i]]%2!=i%2){flag=false;break;}
        for(int i=1;i<n;i++){
            if((i&1)&&(b[i]>b[i+1])){flag=false;break;}
            else if(!(i&1)&&(b[i]<b[i+1])){flag=false;break;}
        }
        ans+=flag;
    }while(next_permutation(b+1,b+n+1));
    printf("%d\n",ans);exit(0);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        s[0][i]=s[0][i-1];s[1][i]=s[1][i-1];
        s[a[i]][i]++;
    }
    if(count(a+1,a+n+1,1)!=(n+1)/2) NO();
    if(n==1)    return puts("1"),0;
    if(!a[1]||a[n]) NO();
    int s=0;
    for(int i=n;i;i--){
        s+=a[i]?-1:1;
        if((n&1)&&(i==1))   continue;
        if(s<0)NO;
    }
    s=0;
    for(int i=1;i<=n;i++){
        s+=a[i]?1:-1;
        if(s<0)NO;
    }
    int sum=2,ans=1;
    s=2;
    for(int i=n-!(n&1);i;i--){
        if(a[i]){
            if(sum<=1)    NO();
            mmul(ans,sum-1);
        }
        else mmul(ans,sum-(n&1));
        sum+=a[i]?-1:1;
        s+=a[i]?-1:1;
        if(sum<=0)  NO();
        if(s<=0)  NO();
    }
    printf("%d\n",ans);
}