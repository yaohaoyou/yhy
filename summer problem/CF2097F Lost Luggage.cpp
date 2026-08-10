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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=15, maxN=(1<<12)+10, maxm=2010;
int n,m,N;
int s[maxn],a[maxm][maxn],b[maxm][maxn],c[maxm][maxn];
// f[j][S][l1][0/1] : 处理到第 i 天第 j 个机场，轮廓线 S，前一天机场 1 的状态 l1，当前机场连通性
int f[maxn][maxN][2][2];  

inline int pr(int x){return (x-2+n)%n+1;}
inline int nx(int x){return x%n+1;}
inline int out(int s,int x){return s&(N^(1<<x-1));}

void matt(int _cases){
    scanf("%d%d",&n,&m); N=(1<<n)-1;
    for(int i=1;i<=n;i++)   scanf("%d",&a[0][i]), b[0][i]=c[0][i]=1e9;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)   scanf("%d",&a[i][j]);
        for(int j=1;j<=n;j++)   scanf("%d",&b[i][j]);
        for(int j=1;j<=n;j++)   scanf("%d",&c[i][j]);
    }

    memset(f, 0x3f, sizeof(f));
    for(int S=0; S<=N; S++){
        int w=0;
        for(int j=1;j<=n;j++) if(!(S&(1<<j-1))) w+=a[0][j];
        int l1 = (S & 1);
        f[0][S][l1][0] = w;
    }

    for(int i=2; i<=m+1; i++){
        for(int j=1; j<=n; j++) memset(f[j], 0x3f, sizeof(f[j]));

        for(int j=1; j<=n; j++){
            for(int S=0; S<=N; S++){
                // 计算 nw 与 w，涉及前一天机场 1 的状态时使用 l1
                int l1 = 0; // 将在下面赋值
                if(j==1){
                    l1 = (S & 1);
                    bool nw = (S&1) || (S&(1<<pr(1)-1)) || (S&(1<<nx(1)-1));
                    int w=0;
                    if(S&1) w+=b[i-1][1];
                    if(S&(1<<pr(1)-1)) w+=c[i-1][pr(1)];
                    if(S&(1<<nx(1)-1)) w+=a[i-1][nx(1)];
                    gmn(f[1][S][l1][nw], f[0][S][l1][0]);
                    gmn(f[1][S][l1][0],  f[0][S][l1][0] + w);
                } else {
                    // j > 1，遍历前一位置传递的 o 和 l1
                    bool c1 = (S & (1<<j-1));
                    for(int o=0; o<2; o++){
                        for(int l1=0; l1<2; l1++){
                            bool c_pr = (pr(j)==1) ? l1 : (S & (1<<pr(j)-1));
                            bool c_nx = (nx(j)==1) ? l1 : (S & (1<<nx(j)-1));
                            bool nw = c1 || c_pr || c_nx;
                            int w=0;
                            if(S & (1<<j-1))      w += b[i-1][j];
                            if(pr(j)==1){
                                if(l1) w += c[i-1][1];
                            } else if(S & (1<<pr(j)-1)) w += c[i-1][pr(j)];
                            if(nx(j)==1){
                                if(l1) w += a[i-1][1];
                            } else if(S & (1<<nx(j)-1)) w += a[i-1][nx(j)];

                            int ns = out(S, j-1) | (o << (j-2));
                            gmn(f[j][ns][l1][nw], f[j-1][S][l1][o]);
                            gmn(f[j][ns][l1][0],  f[j-1][S][l1][o] + w);
                        }
                    }
                }
            }
        }

        memset(f[0], 0x3f, sizeof(f[0]));
        for(int S=0; S<=N; S++){
            for(int l1=0; l1<2; l1++){
                for(int o=0; o<2; o++){
                    if(f[n][S][l1][o] > 1e9) continue;
                    int ns = out(S, n) | (o << (n-1));
                    int nl1 = (ns & 1);
                    gmn(f[0][ns][nl1][0], f[n][S][l1][o]);
                }
            }
        }
        printf("%d\n", f[0][0][0][0]);
    }
}

int main(){
    int T; scanf("%d",&T);
    for(int i=1;i<=T;i++) matt(i);
}