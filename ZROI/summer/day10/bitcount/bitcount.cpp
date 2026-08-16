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
const int maxn=3010,maxm=1e6+10;
int n,mod;
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
bool mem1;
char a[maxn],b[maxn],c[maxn];
int p[maxn];
bool f[maxn][3][maxn],ans[maxm];
bool mem2;
bool chk(char x,char y,char z,bool xx,bool yy,bool zz){return (x=='?'||x-'0'==xx)&&(y=='?'||y-'0'==yy)&&(z=='?'||z-'0'==zz);}
void matt(int _cases){
    for(int i=0;i<=n+2;i++)for(int o=0;o<3;o++)for(int j=0;j<=n+2;j++)f[i][o][j]=0;
    scanf("%d%d",&n,&mod);
    scanf("%s%s%s",a+1,b+1,c+1);
    p[0]=0;p[1]=1%mod;for(int i=2;i<=n+1;i++)p[i]=immul(3,p[i-1]);
    reverse(a+1,a+n+1);reverse(b+1,b+n+1);reverse(c+1,c+n+1);
    // for(int i=1;i<=n;i++)   putchar(a[i]),putchar(' ');puts("");
    // for(int i=1;i<=n;i++)   putchar(b[i]),putchar(' ');puts("");
    // for(int i=1;i<=n;i++)   putchar(c[i]),putchar(' ');puts("");
    f[0][0][1]=1;
    for(int i=1;i<=n;i++){
        char x=a[i],y=b[i],z=c[i];
        for(int j=0;j<3;j++){
            int sta=0;bool f0,f1,f2,f3;f0=f1=f2=f3=0;
            for(int a:{0,1})for(int b:{0,1})for(int c:{0,1})if(chk(x,y,z,a,b,c))sta|=1<<((a<<2)|(b<<1)|c);
            if(chk(x,y,z,0,0,j&1))  f0=1,sta^=1<<(j&1);
            if(chk(x,y,z,0,1,(1+(j&1))&1))    f1=1,sta^=1<<(2|((1+(j&1))&1));
            if(chk(x,y,z,0,1,j&1))  f2=1,sta^=1<<(2|(j&1));
            if(chk(x,y,z,1,1,(1+(j&1))&1))  f3=1,sta^=1<<(6|((1+(j&1))&1));
            // if(i==4)    printf("%d %d %d %d %d\n",f0,f1,f2,f3,sta);
            for(int k=1;k<=n+1;k++)if(f[i-1][j][k]){
                // printf("%d %d 3^%d\n",i-1,j,k-1);
                if(f0)  f[i][j>>1][k]=true;
                if(f1)  f[i][j+1>>1][k+1]=true;
                if(f2)  f[i][(j>>1)+1][k+1]=true;
                if(f3)  f[i][(j+1>>1)+1][k]=true;
                if(sta)  ans[0]=true;
            }
        }
    }
    for(int j=1;j<=n+1;j++)if(f[n][1][j]||f[n][2][j]){ans[0]=true;break;}
    for(int j=1;j<=n+1;j++)if(f[n][0][j])ans[p[j]]=true;
    for(int i=0;i<mod;i++) putchar(ans[i]+'0'),ans[i]=0;puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}