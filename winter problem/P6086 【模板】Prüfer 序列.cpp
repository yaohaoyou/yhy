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
const int maxn=5e6+10;
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
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
int n,m;
int a[maxn],fa[maxn],deg[maxn];
priority_queue<int,vector<int>,greater<int>> q;
int main(){
    n=read();m=read();
    if(m==1){
        fill(deg+1,deg+n,1);
        for(int i=1;i<n;i++)   deg[fa[i]=read()]++;
        if(deg[n]==1)fa[n]=find(fa+1,fa+n,n)-fa;  // 按理来说 n 是叶子时不加这个会错，但是由于 n 的编号最大所以这里去掉也行。但是若本题输入的是 fa[2,n] 就一定要判 1 是不是叶子
        for(int i=1;i<=n;i++)if(deg[i]==1)q.ep(i);
        int m=0;
        while(m^(n-2)){
            int u=q.top();q.pop();a[++m]=fa[u];
            if((--deg[fa[u]])==1)   q.ep(fa[u]);
        }
        ll ans=0;
        for(int i=1;i<=n-2;i++) ans^=(1ll*i*a[i]);
        printf("%lld\n",ans);
    }
    else{
        fill(deg+1,deg+n+1,1);
        for(int i=1;i<=n-2;i++) deg[a[i]=read()]++;
        for(int i=1;i<=n;i++)if(deg[i]==1)q.ep(i);
        for(int i=1;i<=n-2;i++){
            fa[q.top()]=a[i];q.pop();
            if((--deg[a[i]])==1)    q.ep(a[i]);
        }
        fa[q.top()]=n;
        ll ans=0;
        for(int i=1;i<n;i++) ans^=(1ll*i*fa[i]);
        printf("%lld\n",ans);
    }
}