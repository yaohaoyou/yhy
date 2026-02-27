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
const int maxn=3000+10;
int n,m,k;
char s[maxn],t[maxn];
int f[maxn][maxn],fr[maxn][maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void data(){
    srand(time(0));
    n=3000;m=100;k=10;
    printf("%d\n",k);
    for(int i=1;i<=n;i++)putchar(rand()%3+'a');putchar('\n');
    for(int i=1;i<=m;i++)putchar(rand()%3+'a');putchar('\n');
    exit(0);
}
int main(){
    freopen("string.in","r",stdin);freopen("string.out","w",stdout);
    // data();
    scanf("%d%s%s",&k,s+1,t+1);n=strlen(s+1);m=strlen(t+1);
    mems(f,0x3f);
    for(int i=0;i<=m;i++)   f[0][i]=i;
    for(int i=1;i<=n;i++){
        f[i][0]=0;
        for(int j=1;j<=m;j++){
            f[i][j]=min(min(f[i-1][j],f[i][j-1]),f[i-1][j-1])+1;
            if(s[i]==t[j])gmn(f[i][j],f[i-1][j-1]);
            // printf("%d ",f[i][j]);
        }
        // puts("");
    }
    for(int i=1;i<=n;i++){
        if(f[i][m]<=k){
            // int x=i,y=m;
            // while(y^1){
            //     if(!fr[x][y])   x--;
            //     else if(fr[x][y]==1)    y--;
            //     else x--,y--;
            // }
            puts("1 1");
            return 0;
        }
    }
    puts("NO");
}