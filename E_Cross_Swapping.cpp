#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1010;
int n;
int a[maxn][maxn];
namespace IO{
    const int SIZ=1000000;
    static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++
    #define putchar(x) (p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
    #define flush fwrite(obuf,p3-obuf,1,stdout)
    #define if(sth) if(__builtin_expect(sth,1))
    #define while(sth) while(__builtin_expect(sth,1))
    inline int read(){
        int x=0; int f=1; char c=getchar();
        while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
        while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getchar();
        x*=f;
        return x;
    }
    inline void print(int x){ 
        if(!x)return putchar(48),void();
        int len=0;
        if(x<0)x=-x,putchar(45);
        while(x)cc[len++]=x%10+48,x/=10;
        while(len--)putchar(cc[len]);
    }
}
using namespace IO;
void solve(){
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)   a[i][j]=read();
    for(int i=1;i<=n;i++){
        bool flag=false;
        for(int j=1;j<=n;j++){
            if(i==j)    continue;
            if(j<i&&(a[j][i]^a[i][j])){if(a[j][i]>a[i][j])flag=true;else flag=false;break;}
            if(j>i&&(a[i][j]^a[j][i])){if(a[i][j]>a[j][i])flag=true;else flag=false;break;}
        }
        if(!flag)   continue;
        for(int j=1;j<=n;j++)   swap(a[i][j],a[j][i]);
    }
    for(int i=1;i<=n;i++,putchar('\n'))
        for(int j=1;j<=n;j++)   print(a[i][j]),putchar(' ');
}
int main(){
    // freopen("D:\\yhy\\GDFZ_yhy\\swap\\swap4.in","r",stdin);freopen("D:\\yhy\\GDFZ_yhy\\swap\\swap.out","w",stdout);
    int T=read();while(T--)solve();
    flush;
}