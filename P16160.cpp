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
const int maxn=1e6+10,maxm=1e5+10,maxk=310;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
int n,m,k;
vector<int> v[maxk];
ll a[maxn];
int siz;
ll f[maxk][maxm];  // f[i][j] 表示前 i 种物品的体积和为 j 的答案
int opt[maxm];
inline void upd(int i,int x,int j){
    // assert(j%i==x%i);
    ll w=f[k-1][x]+a[min((j-x)/i,siz)];
    if(f[k][j]<w)   f[k][j]=w,opt[j]=x;
}
void solve(int L,int R,int i,int k){
    if(L==R)    return;
    int md=(L+R)>>1,l=L*i+k,r=R*i+k,mid=md*i+k;
    for(int x=opt[l-i]?opt[l-i]:k;x<=opt[r];x+=i)   upd(i,x,mid);
    solve(L,md,i,k);
    for(int x=l;x<=mid;x+=i)   upd(i,x,r);
    solve(md+1,R,i,k);
}
int main(){
    // freopen("C:\\Users\\noi017\\Downloads\\P16160_5.in","r",stdin);
    n=read();m=read();
    for(int i=1;i<=n;i++)   v[read()].eb(read());
    for(int i=1;i<=300;i++){
        sort(v[i].begin(),v[i].end(),greater<int>());
        siz=0;for(int j:v[i])a[++siz]=a[siz]+j;
        if(siz){
            mems(opt,0);
            ++k;mems(f[k],-0x3f);
            for(int l=0;l<i&&l<=m;l++){
                int r=l;while(r<=m)opt[r]=0,r+=i;r-=i;
                if(l<r){
                    upd(i,l,l);upd(i,l,r);
                    solve(1,(r-l)/i,i,l);
                }
            }
            for(int j=0;j<=m;j++)   gmx(f[k][j],f[k-1][j]);
        }
    }
    for(int i=1;i<=m;i++)   print(f[k][i],' ');flush();
}