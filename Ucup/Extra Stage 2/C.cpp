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
const int maxn=1e3+10,dir[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
int n,m;
int a[maxn][maxn],c[maxn][maxn];
int b[6][6]={
    {0,1,1,2,2,0},
    {1,0,2,1,0,2},
    {2,2,0,0,1,1},
    {2,2,0,0,1,1},
    {1,0,2,1,0,2},
    {0,1,1,2,2,0},
};
void data(){
    n=m=1;
    while(n%3&&m%3){n=rand()%100+1;m=rand()%100+1;}
    printf("%d %d\n",n,m);
}
struct DSU{
    int fa[maxn*maxn];
    void init(){iota(fa+1,fa+n*m-1+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
inline int id(int x,int y){return x*m+y;}
bool check(){
    int cnt[3]={0,0,0};
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)cnt[c[i][j]]++;
    if(cnt[0]!=cnt[1]||cnt[1]!=cnt[2])  return false;
    for(int i=0;i<n;i++)for(int j=0;j+2<m;j++)if(c[i][j]==c[i][j+1]&&c[i][j]==c[i][j+2])return false;
    for(int i=0;i+2<n;i++)for(int j=0;j<m;j++)if(c[i][j]==c[i+1][j]&&c[i][j]==c[i+2][j])return false;
    U.init();
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        for(int k=0;k<8;k++){
            int x=i+dir[k][0],y=j+dir[k][1];
            if(x>=0&&x<n&&y>=0&&y<m&&c[x][y]==c[i][j])U.merge(id(i,j),id(x,y));
        }
    }
    int rt[3]={-1,-1,-1};
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        if(!~rt[c[i][j]])   rt[c[i][j]]=U[id(i,j)];
        else if(rt[c[i][j]]^U[id(i,j)])return false;
    }
    return true;
}
void matt(int _cases){
    scanf("%d%d",&n,&m);
    bool flag=false;
    if(n%3){
        swap(n,m);
        flag=true;
    }
    if(n%3==0&&m%3==0&&n>m) swap(n,m),flag=true;
    if(n==6&&m==1){
        if(flag)   return puts("Yes\n001122"),void();
        else return puts("Yes\n0\n0\n1\n1\n2\n2"),void();
    }
    if(n==6&&m==2){
        if(flag)   return puts("Yes\n001122\n001122"),void();
        else return puts("Yes\n00\n00\n11\n11\n22\n22"),void();
    }
    else if(m==4){
        if(!(n&1)){for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[i][j]=b[j%6][i%6];}
        else{
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[i][j]=b[j%6][i%6];
            a[n-1][1]=1;
        }
    }
    else{
        for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[i][j]=b[i%6][j%6];
    }
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)c[i][j]=a[i][j];
    if(flag){
        for(int i=0;i<n;i++)for(int j=0;j<m;j++)c[m-1-j][i]=a[i][j];
        swap(n,m);
    }
    if(!check()) return puts("No"),void();
    puts("Yes");
    for(int i=0;i<n;i++,puts(""))for(int j=0;j<m;j++)printf("%d",c[i][j]);
}
int main(){srand(time(0));int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}