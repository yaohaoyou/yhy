#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define db long double
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1010;
int n,T;
int a[maxn];
db P,pq[maxn];
db f[maxn][2];  // f[i][0/1] 表示 i 个人中（不确定有无/有）人是阳性时，找出第一个阳性的人的最少期望步数
int op[maxn][2];
bool ans[maxn];
inline bool ask(int l,int r){printf("Q ");for(int i=1;i<=n;i++)if(i>=l&&i<=r)putchar('1');else putchar('0');puts("");fflush(stdout);char c[5];scanf("%s",c);return c[0]=='P';}
bool solve(int l,int r,bool o=false){
    if(l>r) return 0;
    if(l==r)    return ans[l]=o?1:ask(l,r);
    int x=r-l+1,len=op[x][o];
    if(ask(l,l+len-1))  return solve(l,l+len-1,true);
    else    return solve(l+len,r,o);
}
void matt(int _cases){
    mems(ans,0);
    // solve(1,n);
    int l=1;
    while(solve(l,n)){
        for(int i=n;i;i--)if(ans[i]){l=i+1;break;}
    }
    printf("A ");for(int i=1;i<=n;i++)printf("%d",ans[i]);puts("");fflush(stdout);
    scanf("%*s");
}
int main(){
    scanf("%d%LF%d",&n,&P,&T);
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=pq[i-1]*(1-P);
    f[1][0]=1;
    for(int i=2;i<=n;i++){
        f[i][0]=f[i][1]=1e9;
        for(int j=1;j<i;j++){
            db p=(1-pq[j])/(1-pq[i]),w=p*f[j][1]+(1-p)*f[i-j][1]+1;
            if(w<f[i][1])   f[i][1]=w,op[i][1]=j;
        }
        for(int j=1;j<=i;j++){
            db p=1-pq[j],w=p*f[j][1]+(1-p)*f[i-j][0]+1;
            if(w<f[i][0])   f[i][0]=w,op[i][0]=j;
        }
        // printf("%.2LF %.2LF\n",f[i][0],f[i][1]);
        // printf("%d %d\n",op[i][0],op[i][1]);
    }
    // printf("%.5LF\n",f[n][0]);
    for(int i=1;i<=T;i++)matt(i);
}