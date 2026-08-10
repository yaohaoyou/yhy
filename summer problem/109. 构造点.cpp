#include<bits/stdc++.h>
#define int __int128
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
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
void data(){
    int T=100;
    printf("%d\n",T);
    while(T--){printf("%d %d %d %d %d %d\n",rand()%10,rand()%10,rand()%10,rand()%10,rand()%10,rand()%10);}
    exit(0);
}
main(){
    // data();
    int q=read();
    for(int i=1;i<=q;i++){
        int x1=read(),y1=read(),x2=read(),y2=read(),x3=read(),y3=read();
        if(x3>x1)   swap(x1,x3),swap(y1,y3);
        if(x3>x2)   swap(x2,x3),swap(y2,y3);
        x1-=x3;x2-=x3;y1-=y3;y2-=y3;
        bool rs=0,rx=0,ry=0;
        if(!x1){rs=1;swap(x1,y1);swap(x2,y2);}
        stack<int> s;
        while(true){
            int k=y1/x1;s.ep(k);
            // printf("(%lld,%lld) (%lld,%lld) %d\n",x1,y1,x2,y2,k);
            y1-=k*x1;y2-=k*x2;
            if(!y1) break;
            swap(x1,y1);swap(x2,y2);
        }
        // printf("(%lld,%lld) (%lld,%lld)\n",x1,y1,x2,y2);
        if(x1<0)    x1*=-1,x2*=-1,rx=1;
        if(y2<0)    y2*=-1,ry=1;
        int k=0,x=1,y=1;
        if(x2<0)    k=x2,x2-=k*y2;
        k+=x2/y2;x2-=x2/y2*y2;
        // printf("%lld (%lld,%lld)\n",x1,x2,y2);
        if(x2==x1){
            if(x1<=1){pus("-1 -1\n");continue;}
        }
        else{
            // double k=1.0*y2/(x2-x1);
            // printf("y = %.2fx+%.2f\n",k,b);
            // printf("%.2f\n",-b/(k-1));
            if(x2>x1){
                if(y2>x2-x1){
                    if(y2*x1<=y2-(x2-x1)){pus("-1 -1\n");continue;}
                }
                else{
                    if(y2*x1>=y2-(x2-x1)){pus("-1 -1\n");continue;}
                }
            }
            else{
                if(y2<x2-x1){
                    if(y2*x1>=y2-(x2-x1)){pus("-1 -1\n");continue;}
                }
                else{
                    if(y2*x1<=y2-(x2-x1)){pus("-1 -1\n");continue;}
                }
            }
            // if(-b/(k-1)<=1){pus("-1 -1\n");continue;}
        }
        x+=k*y;
        if(rx)x*=-1;if(ry)y*=-1;
        swap(x,y);
        while(!s.empty()){
            swap(x,y);
            y+=s.top()*x;
            s.pop();
        }
        if(rs)  swap(x,y);
        assert(x+x3>0&&y+y3>0);
        print(x+x3,' ');print(y+y3,'\n');
    }
    flush();
}