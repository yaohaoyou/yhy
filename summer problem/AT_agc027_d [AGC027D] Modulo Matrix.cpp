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
const int maxn=510,N=1e7,dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int n;
ll a[maxn][maxn];
vector<int> p;
bool ntpri[N+10];
void seive(){
    for(int i=2;i<=N;i++){
        if(!ntpri[i])   p.eb(i);
        for(int j:p){
            if(1ll*i*j>N)   break;
            ntpri[i*j]=true;
            if(i%j==0)  break;
        }
    }
}
inline ll lcm(ll x,ll y){return (!x||!y)?(x|y):x/__gcd(x,y)*y;}
int main(){
    seive();
    scanf("%d",&n);
    bool flag=n&1;
    if(!flag)   n++;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=1;
    int c=-1;
    for(int i=1;i<=n;i+=2){
        c++;
        int x=1,y=i;
        while(x<=n&&y<=n){a[x][y]*=p[c];x++;y++;}
    }
    for(int i=3;i<=n;i+=2){
        c++;
        int x=i,y=1;
        while(x<=n&&y<=n){a[x][y]*=p[c];x++;y++;}
    }
    for(int i=1;i<=n;i+=2){
        c++;
        int x=1,y=i;
        while(x<=n&&y>0){a[x][y]*=p[c];x++;y--;}
    }
    for(int i=3;i<=n;i+=2){
        c++;
        int x=i,y=n;
        while(x<=n&&y>0){a[x][y]*=p[c];x++;y--;}
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if(a[i][j]^1)    continue;
            ll b[4]={0,0,0,0};
            for(int d=0;d<4;d++){
                int x=i+dir[d][0],y=j+dir[d][1];
                if(x>0&&y>0&&x<=n&&y<=n)    b[d]=a[x][y];
            }
            a[i][j]=lcm(lcm(b[0],b[1]),lcm(b[2],b[3]));
            a[i][j]++;
        }
    n-=!flag;
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%lld ",a[i][j]);
}