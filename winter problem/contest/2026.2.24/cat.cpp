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
const int maxn=22,mod=998244353;
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
int n,bell;
int bel[maxn],a[maxn][maxn],buc[maxn];
inline int A(int x,int y){
    if(x<y)return 0;
    int res=1;
    for(int i=x-y+1;i<=x;i++)mmul(res,i);
    return res;
}
void dfs(int x,int y){
    if(x>n){
        bell++;
        buc[y]++;
        return;
    }
    bel[x]=y+1;
    dfs(x+1,y+1);
    for(int i=1;i<=y;i++){
        bool flag=true;
        for(int j=1;j<=x;j++)if(a[x][j]&&bel[j]==i){flag=false;break;}
        if(!flag)   continue;
        bel[x]=i;
        dfs(x+1,y);
    }
}
int cir(int x,int k){return x==2?immul(k,k-1):imdel(immul(k,qpow(k-1,x-1)),cir(x-1,k));}
int main(){
    int c;
    scanf("%d%d",&c,&n);
    // printf("%d\n",cir(c,n));exit(0);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
    int T;scanf("%d",&T);
    if(c==2){
        while(T--){int k,ans;scanf("%d",&k);ans=immul(k,qpow(k-1,n-1));mmul(ans,qpow(qpow(k,n),mod-2));printf("%d\n",ans);}
        return 0;
    }
    if(c==3){
        while(T--){int k,ans;scanf("%d",&k);ans=cir(n,k);mmul(ans,qpow(qpow(k,n),mod-2));printf("%d\n",ans);}
        return 0;
    }
    dfs(1,0);
    while(T--){
        int k,ans=0;scanf("%d",&k);
        for(int i=1;i<=n;i++)if(buc[i])madd(ans,immul(A(k,i),buc[i]));
        mmul(ans,qpow(qpow(k,n),mod-2));
        printf("%d\n",ans);
    }
    // printf("bell(%d) = %d\n",n,bell);
}