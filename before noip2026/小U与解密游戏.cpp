#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ef emplace_front
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;
bool mem1;
const int maxn=5e6+10;
int n,m,k;
int a[maxn],ans[maxn];
deque<pii> q;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();k=read();
    for(int i=1;i<=n;i++)if(!read())a[++m]=i;
    int cnt=0;
    if(n-a[m]>0)    q.eb(min(k,n-a[m]),1);
    if(n-a[m]<k)    q.eb(k-(n-a[m]),0),cnt=k-(n-a[m]);
    ans[m]=a[m]+k-cnt;
    for(int i=m-1;i;i--){
        if(cnt<a[i+1]-a[i]-1){
            q.clear();q.eb(k,1);cnt=0;
        }
        else{
            int now=0,stp=0;
            if(a[i+1]==a[i]+1){
                if(!q.front().se)   q.front().fi++;
                else q.ef(1,0);
                cnt++;
            }
            else{
                while(!q.empty()){
                    if(!q.front().se&&now+q.front().fi>=a[i+1]-a[i]-1){
                        cnt-=q.front().fi;
                        int x=q.front().fi,d=a[i+1]-a[i]-1-now;q.pop_front();
                        stp+=d;
                        q.ef(x-d+1,0);if(stp)q.ef(stp,1);
                        cnt+=x-d+1;
                        break;
                    }
                    stp+=q.front().fi;
                    if(!q.front().se)   now+=q.front().fi,cnt-=q.front().fi;
                    q.pop_front();
                }
            }
            if(q.back().fi>1)   q.back().fi--,cnt-=!q.back().se;
            else    cnt-=!q.back().se,q.pop_back();
        }
        ans[i]=a[i]+k-cnt;
    }
    fill(a+1,a+n+1,1);
    for(int i=1;i<=m;i++)   a[ans[i]]=0;
    for(int i=1;i<=n;i++)   print(a[i],' ');FastIO::flush();
}