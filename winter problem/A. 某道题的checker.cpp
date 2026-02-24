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
const int maxn=5e5+10,maxm=25,maxM=(1<<22)+10;
bool mem1;
int n,m;
int a[maxn],ans[maxn];
vector<int> b[maxm];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
bool mem2;
mt19937 matt(time(0));
inline int rd(){return abs(int(matt()));}
void data(){
    n=5e5;m=22;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++)   printf("%d ",rd()&((1<<m)-1));
    puts("");
    exit(0);
}
int main(){
    // data();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();m=read();const int M=1<<m;
    for(int i=1;i<=n;i++){
        a[i]=read();
        vector<int> tmp;tmp.clear();
        for(int j=0;j<m;j++)tmp.eb(bool(a[i]&(1<<j)));
        a[i]=0;for(int j=0;j<m;j++)a[i]=a[i]<<1|tmp[j];
    }
    for(int i=0;i<m;i++)   b[i].resize(1<<i);
    for(int i=2;i<=n;i++){
        int x=a[i-1]^a[i],s=0;
        for(int j=0;j<m;j++){
            if(!(x&(1<<j))) continue;
            if(a[i]&(1<<j)) b[j][s]++;
            s|=1<<j;
        }
    }
    for(int i=0;i<m;i++){
        const int x=1<<i;
        for(int j=0;j<i;j++){
            for(int k=0;k<x;k++)if(k&(1<<j))b[i][k]+=b[i][k^(1<<j)];
        }
    }
    for(int i=0;i<M;i++){
        int x=0,s=0;
        for(int j=0;j<m;j++){
            if(i&(1<<j))    x|=1<<j;
            else    s+=b[j][x];
        }
        ans[s]++;
    }
    for(int i=0;i<n;i++)    print(ans[i]),putc(' ');flush();
}