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
const int maxn=3e5+10,lgB=9,B=1<<lgB;
bool mem1;
int a[maxn],dis[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
int n,m;
namespace Block_array{
    const int Block=maxn/B+10;
    #define id(x) ((((x)-1)>>lgB)+1)
    #define bl(x) ((((x)-1)<<lgB)+1)
    #define br(x) min(n,(x)<<lgB)
    int tag[Block],pos[Block];
    pii d[Block][B+10];
    inline void broke(int x){
        int l=bl(x),r=br(x);
        for(int i=l;i<=r;i++)   dis[i]+=tag[x],d[x][i-l+1].fi+=tag[x];
        tag[x]=0;
    }
    inline void rebuild(int x,bool flag=false){
        int l=bl(x),r=br(x);
        if(flag)for(int i=l;i<=r;i++)   d[x][i-l+1]=pii(dis[i],i);
        // pos[x]=0;
        // while(pos[x]<r-l+1&&d[x][pos[x]+1].fi<=m)  pos[x]++;
        pos[x]=upper_bound(d[x]+1,d[x]+r-l+2,pii(m,1e9))-d[x]-1;
    }
    pii vec[maxn];
    inline void add(int l,int r,int s){
        int x=id(l),L=bl(x),R=br(x);
        broke(x);
        for(int i=l;i<=r;i++)   dis[i]+=s;
        int p=0,pp=0;
        for(int i=1;i<=R-L+1;i++)if(d[x][i].se>=l&&d[x][i].se<=r)vec[++pp]=pii(d[x][i].fi+s,d[x][i].se);else d[x][++p]=d[x][i];
        int q=p;
        for(int _=1;_<=pp;_++)  d[x][++q]=vec[_];
        inplace_merge(d[x]+1,d[x]+p+1,d[x]+q+1);
        rebuild(x);
    }
    inline void upd(int l,int r,int s){
        int idl=id(l),idr=id(r);
        if(idl==idr)    return add(l,r,s);
        if(l^n)add(l,br(idl),s);else idl--;if(r^n)add(bl(idr),r,s);

        for(int i=idl+1;i<idr;i++){
            tag[i]+=s;
            const int li=B;
            while(pos[i]<li&&d[i][pos[i]+1].fi+tag[i]<=m)  pos[i]++;
            while(pos[i]&&d[i][pos[i]].fi+tag[i]>m)  pos[i]--;
        }
        const int i=idr,li=n-bl(i)+1;
        tag[i]+=s;
        while(__builtin_expect(pos[i]<li&&d[i][pos[i]+1].fi+tag[i]<=m,1))  pos[i]++;
        while(__builtin_expect(pos[i]&&d[i][pos[i]].fi+tag[i]>m,0))  pos[i]--;
    }
    inline int query(int l,int r){
        int idl=id(l),idr=id(r),res=0;
        if(idl==idr){
            for(int i=l;i<=r;i++)   res+=(dis[i]+tag[idl]<=m);
            return res;
        }
        for(int i=l,R=br(idl);i<=R;i++) res+=(dis[i]+tag[idl]<=m);
        if(r^n){for(int i=bl(idr);i<=r;i++) res+=(dis[i]+tag[idr]<=m);}
        else idr++;
        
        for(int i=idl+1;i<idr;i++)  res+=pos[i];
        return res;
    }
}
using namespace Block_array;
bool mem2;
int ans[maxn];
int main(){
    // freopen("jump.in","r",stdin);freopen("jump.out","w",stdout);
    n=read();m=read();
    for(int i=1;i<n;i++) a[i]=read();
    for(int i=1;i<=id(n);i++)   rebuild(i,true);
    for(int i=n;i;i--){
        if(i^n){
            int v=-dis[a[i]]-tag[id(a[i])];
            upd(a[i],n,v);
            upd(i+1,n,1);
        }
        ans[i]=query(i,n);
    }
    for(int i=1;i<=n;i++)  print(ans[i]),putc(' ');flush();
}