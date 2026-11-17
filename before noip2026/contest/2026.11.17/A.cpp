#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){if(x>y)x=y;}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e6+10,maxm=maxn*3,inf=1e9;
bool mem1;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
int n,m,k;
piii a[maxn],d[maxn<<1];
int b[maxm],f[maxm],p[maxm],ch[maxm];
bool ans[maxm];
pii stk[maxm];int tp;
void discrete(){
    k=0;
    b[++k]=1;
    for(int i=1;i<=m;i++)   b[++k]=a[i].fi.fi,b[++k]=a[i].fi.se,b[++k]=a[i].se;
    sort(b+1,b+k+1);k=unique(b+1,b+k+1)-b-1;
    for(int i=1;i<=m;i++)   a[i].fi.fi=lower_bound(b+1,b+k+1,a[i].fi.fi)-b,a[i].fi.se=lower_bound(b+1,b+k+1,a[i].fi.se)-b,a[i].se=lower_bound(b+1,b+k+1,a[i].se)-b;
}
bool mem2;
void matt(int _cases){
    n=read();m=read();
    bool flg=false;
    for(int i=1;i<=m;i++)   a[i].fi.fi=read(),a[i].fi.se=read(),a[i].se=read(),flg|=a[i].se==n;
    if(!flg)    return pus("-1\n"),void();
    discrete();
    n=0;
    for(int i=1;i<=m;i++)d[++n]=piii(pii(a[i].fi.fi,a[i].fi.se),-i),d[++n]=piii(pii(a[i].fi.se,a[i].se),i);
    sort(d+1,d+n+1,[&](piii x,piii y){return x.fi.se<y.fi.se;});
    fll(f,1e9,k);
    tp=f[1]=0;stk[++tp]=pii(1,0);
    int j=1;while(j<=n&&d[j].fi.se==1)j++;
    for(int i=2;i<=k;i++){
        ch[i]=0;
        while(j<=n&&d[j].fi.se==i){
            int tmp=lower_bound(stk+1,stk+tp+1,pii(d[j].fi.fi,0))-stk;
            if(tmp<=tp){
                pii q=stk[tmp];swap(q.fi,q.se);
                // printf("%d : %d %d\n",d[j].fi.fi,q.fi,q.se);
                int t=q.fi+bool(d[j].se>0);
                if(f[i]>t){
                    f[i]=t,p[i]=q.se;
                    if(d[j].se>0)   ch[i]=d[j].se;
                    else    ch[i]=0;
                }
            }
            j++;
        }
        while(tp&&stk[tp].se>=f[i]) tp--;
        stk[++tp]=pii(i,f[i]);
    }
    if(f[k]>n)   pus("-1\n");
    else{
        fll(ans,0,m);
        print(f[k],'\n');
        int x=k;
        while(x){
            if(ch[x])   ans[ch[x]]=true;
            x=p[x];
        }
        for(int i=1;i<=m;i++)print(ans[i]);putc('\n');
    }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);Flush();}