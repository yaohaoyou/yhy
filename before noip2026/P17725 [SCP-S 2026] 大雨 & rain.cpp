// 这一发没有垃圾回收，但是更快些，要垃圾回收看上一发
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
const int maxn=1e6+10,lgV=30;
bool mem1;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline int readll(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
int n;
int a[maxn],f[maxn],g[maxn];
inline int LG(int x){return x?31-__builtin_clz(x):0;}
const int maxp=maxn*30;
namespace Trie{
    int rt,tot;
    int stk[maxn],sl;
    int tag[maxp][2],son[maxp][2];bool fll[maxp];
    inline int nd(){
        int p=++tot;
        tag[p][0]=tag[p][1]=son[p][0]=son[p][1]=fll[p]=0;
        return p;
    }
    inline void pd(int p,int d){
        if(!p)  return;
        if(tag[p][0]&tag[p][1]) return;
        if(fll[p]){
            son[p][0]=nd();son[p][1]=nd();
            fll[son[p][0]]=fll[son[p][1]]=true;
            fll[p]=0;
        }
        if(tag[p][0]){
            if(tag[p][0]&(1<<d)) son[p][0]=0;
            else    tag[son[p][0]][0]|=tag[p][0],tag[son[p][1]][0]|=tag[p][0];
            tag[p][0]=0;
        }
        if(tag[p][1]){
            if(tag[p][1]&(1<<d)) son[p][1]=0;
            else    tag[son[p][0]][1]|=tag[p][1],tag[son[p][1]][1]|=tag[p][1];
            tag[p][1]=0;
        }
        if(tag[son[p][0]][0]&tag[son[p][0]][1]) son[p][0]=0;
        if(tag[son[p][1]][0]&tag[son[p][1]][1]) son[p][1]=0;
    }
    inline void asn(int &p){if(!p)p=nd();fll[p]=true;tag[p][0]=tag[p][1]=son[p][0]=son[p][1]=0;}
    void ins(int &p,int d,int x,int y){
        if(!p)  p=nd();
        if(!~d||!(y&((1<<d+1)-1))) return asn(p);
        pd(p,d);
        bool o=x&(1<<d),c=y&(1<<d);
        if(c)   return ins(son[p][!o],d-1,x,y);
        asn(son[p][!o]);ins(son[p][o],d-1,x,y);
    }
    int query(int p,int d,int x,int w){
        if(!p)  return -1;
        if(!~d) return w;
        pd(p,d);
        bool o=x&(1<<d);
        if(son[p][o]){int res=query(son[p][o],d-1,x,w);if(~res)return res;}
        int res=query(son[p][!o],d-1,x,w|(1<<d));
        if(!~res)   son[p][0]=son[p][1]=0;
        return res;
    }
    inline void limit(int x,bool o){tag[rt][o]|=1<<x;}
    void prt(int p,int d){
        printf("%d %d : %d %d %d\n",d,p,tag[p][0],tag[p][1],fll[p]);
        if(!~d)return;
        pd(p,d);
        if(son[p][0])   printf("%d %d 0\n",p,son[p][0],0),prt(son[p][0],d-1);
        if(son[p][1])   printf("%d %d 1\n",p,son[p][1],1),prt(son[p][1],d-1);
    }
}
using namespace Trie;
bool mem2;
void matt(int _cases){
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    if(count(a+1,a+n+1,0)==n)   return puts("0"),void();
    int ans=1;
    pii sta=pii(0,0);
    f[1]=1;
    for(int i=1;i<n;i++)if(a[i]^a[i+1]){
        int x=LG(a[i]^a[i+1]);
        if(sta.fi&(1<<x)){
            if((a[i]&(1<<x))^(sta.se&(1<<x))){
                ans++;
                sta=pii(0,0);
            }
        }
        else    sta.fi|=1<<x,sta.se|=(a[i]&(1<<x));
        f[i+1]=ans;
    }
    else    f[i+1]=ans;
    g[0]=g[1]=0;
    for(int l=0,r=0;r<=n;){
        rt=sl=tot=0;
        int i=r+1;
        while(i<n&&f[i+1]==f[i])i++;
        for(int j=l;j<=i;j++){
            if((j>max(1,l))&&(a[j]^a[j-1])){
                int x=LG(a[j]^a[j-1]);
                limit(x,a[j]&(1<<x));
            }
            if(j&&(~g[j-1])&&j<=r+1)  ins(rt,lgV,a[j],g[j-1]);
            if(j>r) g[j]=query(rt,lgV,a[j],0);
        }
        l=r+1;r=i;
    }
    // for(int i=1;i<=n;i++)if(f[i]==f[i-1])assert(g[i]>=g[i-1]);
    // printf("max = %lld\n",__lg(*max_element(g+1,g+n+1)));
    for(int i=n-1;~i;i--){
        if((~g[i])&&g[i]<=a[i+1])    ans=min(ans,f[i]);
        if(a[i]>a[i+1]) break;
    }
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);read();int T=read();for(int i=1;i<=T;i++)matt(i);}