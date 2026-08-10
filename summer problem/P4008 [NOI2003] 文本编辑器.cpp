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
mt19937 matt(20250816);
const int maxn=2097152+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline string reads(){string s="";char c=getc();while(!isalpha(c))c=getc();while(isalpha(c))s+=c,c=getc();return s;}
}
using FastIO::read;using FastIO::reads;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
int n,q;
namespace FHQTreap{
    int rt,cur;
    int siz[maxn],ls[maxn],rs[maxn],rd[maxn];
    char val[maxn];
    inline int nd(char v){int p=++cur;val[p]=v;rd[p]=matt();siz[p]=1;return p;}
    inline void pu(int p){siz[p]=siz[ls[p]]+siz[rs[p]]+1;}
    int merge(int x,int y){
        if(!x||!y)  return x|y;
        if(rd[x]>rd[y]){rs[x]=merge(rs[x],y);pu(x);return x;}
        ls[y]=merge(x,ls[y]);pu(y);return y;
    }
    void split(int p,int v,int &x,int &y){
        if(!p)  return x=y=0,void();
        if(siz[ls[p]]>=v)   split(ls[p],v,x,ls[y=p]);
        else    split(rs[p],v-siz[ls[p]]-1,rs[x=p],y);
        pu(p);
    }
    void prt(int p){if(ls[p])prt(ls[p]);putc(val[p]);if(rs[p])prt(rs[p]);}
}
using namespace FHQTreap;
int main(){
    q=read();
    int p=0;
    while(q--){
        string opt=reads();int s;
        if(opt[0]=='M') p=read();
        if(opt[0]=='I'){
            int x,y;
            split(rt,p,x,y);rt=x;
            s=read();
            while(s--){
                char c=getc();
                while(c<32||c>126)c=getc();
                rt=merge(rt,nd(c));
            }
            rt=merge(rt,y);
        }
        if(opt[0]=='D'){
            int x,y,z,era;s=read();
            split(rt,p,x,y);split(y,s,era,z);
            rt=merge(x,z);
        }
        if(opt[0]=='G'){
            int x,y,z,w;s=read();
            split(rt,p,x,y);split(y,s,z,w);
            prt(z);putc('\n');rt=merge(x,merge(z,w));
        }
        if(opt[0]=='P') p--;
        if(opt[0]=='N') p++;
    }
    flush();
}