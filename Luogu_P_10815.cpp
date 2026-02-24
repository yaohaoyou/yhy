#include<bits/stdc++.h>
using namespace std;
namespace IO{
    const int SIZ=1000000;
    static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++
    #define putchar(x) (p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
    #define flush fwrite(obuf,p3-obuf,1,stdout)
    #define if(sth) if(__builtin_expect(sth,1))
    #define while(sth) while(__builtin_expect(sth,1))
    #define i128 __int128
    #define ll long long
    string string_read(){
        string ss="";
        char ch=getchar();
        while(ch!='\n'&&ch!=EOF&&ch!='\r\n'){
            ss=ss+ch;
            ch=getchar();
        }
        return ss;
    }
    inline int read(){
        int x=0; int f=1; char c=getchar();
        while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
        while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getchar();
        x*=f;
        return x;
    }
    inline ll readll(){
        ll x=0; int f=1; char c=getchar();
        while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
        while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getchar();
        x*=f;
        return x;
    }
    inline i128 read128(){
        i128 x=0; int f=1; char c=getchar();
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
    inline void printll(ll x){ 
        if(!x)return putchar(48),void();
        int len=0;
        if(x<0)x=-x,putchar(45);
        while(x)cc[len++]=x%10+48,x/=10;
        while(len--)putchar(cc[len]);
    }
    inline void print128(i128 x){ 
        if(!x)return putchar(48),void();
        int len=0;
        if(x<0)x=-x,putchar(45);
        while(x)cc[len++]=x%10+48,x/=10;
        while(len--)putchar(cc[len]);
    }
}
using namespace IO;
ll ans;
int main(){
    int n=read();
    for(int i=1;i<=n;i++)ans+=read();
    printll(ans);
	flush;
}