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
const int maxn=1510;
int n,s,m,k;
int a[maxn],b[maxn],pre[maxn];
bool cont[maxn];
pii p[maxn];
int dp[maxn][2];  // dp[i][j] 表示上一个选择了区间 i 选了 j 个区间的最多 <=x 的个数
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){gmx(tr[x],s);x+=lowbit(x);}}
    inline int que(int x){int res=-1e9;while(x){gmx(res,tr[x]);x^=lowbit(x);}return res;}
    void clear(){for(int i=0;i<=n;i++)tr[i]=-1e9;}
}t1[2];
struct BIT2{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x){gmx(tr[x],s);x^=lowbit(x);}}
    inline int que(int x){int res=-1e9;while(x<=n){gmx(res,tr[x]);x+=lowbit(x);}return res;}
    void clear(){for(int i=0;i<=n;i++)tr[i]=-1e9;}
}t2[2];
bool check(int x){
    mems(dp,0);
    for(int i=1;i<=n;i++)   pre[i]=pre[i-1]+(b[i]<=x);
    t1[0].clear();t2[0].clear();
    t1[1].clear();t2[1].clear();
    // printf("x = %d\n",x);
    for(int i=1;i<=s;i++){
        dp[i][1]=pre[p[i].se]-pre[p[i].fi-1];
        t1[1].add(p[i].se,dp[i][1]);
        t2[1].add(p[i].se,dp[i][1]-pre[p[i].se]);
        // printf("%d %d : %d\n",i,1,dp[i][1]);
    }
    for(int j=2;j<=m;j++){
        t1[j&1].clear();t2[j&1].clear();
        for(int i=j;i<=s;i++){
            dp[i][j&1]=0;
            // for(int l=1;l<i;l++){
            //     int L=max(p[l].se+1,p[i].fi);
            //     gmx(dp[i][j&1],dp[l][(j-1)&1]+pre[p[i].se]-pre[L-1]);
            // }
            gmx(dp[i][j&1],t1[(j-1)&1].que(p[i].fi-1)+pre[p[i].se]-pre[p[i].fi-1]);
            gmx(dp[i][j&1],t2[(j-1)&1].que(p[i].fi)+pre[p[i].se]);
            t1[j&1].add(p[i].se,dp[i][j&1]);
            t2[j&1].add(p[i].se,dp[i][j&1]-pre[p[i].se]);
        }
    }
    for(int i=1;i<=s;i++)if(dp[i][m&1]>=k)return true;
    return false;
}
int main(){
    scanf("%d%d%d%d",&n,&s,&m,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=s;i++)   scanf("%d%d",&p[i].fi,&p[i].se);
    sort(p+1,p+s+1,[&](pii x,pii y){return x.se<y.se;});
    fill(a+1,a+n+1,1);
    for(int i=1;i<=s;i++)for(int j=1;j<=s;j++)if(i!=j&&p[i].fi<=p[j].fi&&p[j].se<=p[i].se)a[i]++,cont[j]=true;
    int l=1,r=1e9,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
}