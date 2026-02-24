#include<bits/stdc++.h>
#define db double
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
const int maxn=110;
int n;
int a[maxn];
int f[maxn][maxn];
int buc[maxn];
map<int,int> mp;
inline int lb(int x){return x&-x;}
random_device sd;
mt19937 gen(sd());
uniform_int_distribution<int> Matt(0,(1<<30)-1);
inline int rd(){return Matt(gen);}
inline int query(int l,int r){
    int x;scanf("%d",&x);return x;
    int res=0;
    for(int i=l;i<=r;i++)   res^=a[i];
    if(!res)    return -1;
    return __lg(res);
}
db sum;
inline int ask(int l,int r){buc[r-l+1]++;printf("? %d %d\n",l,r);fflush(stdout);sum+=1.0/(r-l+1);int x=query(l,r);return x;}
queue<pii> q;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   a[i]=rd();
    sum=0;
    for(int i=0;i<=n+1;i++)for(int j=0;j<=n+1;j++)f[i][j]=-2;
    for(int len=n;len;len--){
        for(int l=1,r=len;r<=n;l++,r++){
            for(int i=r;i<=n;i++){
                if(f[l][i]==-2||f[r+1][i]==-2) continue;
                if(f[l][i]^f[r+1][i]){f[l][r]=max(f[l][i],f[r+1][i]);break;}
            }
            for(int i=1;i<=l;i++){
                if(f[i][r]==-2||f[i][l-1]==-2) continue;
                if(f[i][r]^f[i][l-1]){f[l][r]=max(f[i][r],f[i][l-1]);break;}
            }
            if(f[l][r]==-2) f[l][r]=ask(l,r);
            for(int i=r+1;i<=n;i++){
                if(f[l][i]==-2) continue;
                if(f[l][i]^f[l][r]) f[i+1][r]=max(f[l][i],f[l][r]);
            }
            for(int i=1;i<=l;i++){
                if(f[i][r]==-2) continue;
                if(f[i][r]^f[l][r]) f[i][l-1]=max(f[i][r],f[l][r]);
            }
            for(int i=r+1;i<=n;i++){
                if(f[r+1][i]==-2) continue;
                if(f[r+1][i]^f[l][r])   f[l][i]=max(f[l][r],f[r+1][i]);
            }
            for(int i=1;i<l;i++){
                if(f[i][l-1]==-2) continue;
                if(f[i][l-1]^f[l][r])   f[i][r]=max(f[i][l-1],f[l][r]);
            }
        }
    }
    puts("!");
    for(int i=1;i<=n;i++,puts(""))for(int j=i;j<=n;j++)printf("%d ",f[i][j]);
    fflush(stdout);
    // for(int i=1;i<=n;i++){debug("(%d,%d) ",i,buc[i]);if(i%10==0)debug("\n");}debug("\n");
    // debug("sum = %.5f\n",sum);
    // for(int i=1;i<=n;i++)   mp[lb(rd())]++;
    // for(auto [i,j]:mp)  printf("%d : %d\n",i,j);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}