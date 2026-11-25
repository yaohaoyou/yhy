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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=5e5+10,mod=998244353;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
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
bool mem1;
int n;
int a[maxn],r[maxn],R[maxn],b[maxn];
mit f[maxn],sf[maxn],SF[maxn],g[maxn];
int buc[maxn],nx[maxn];
vector<int> v[maxn],s[maxn];
bool mem2;
void matt(int _cases){
    mems(buc,0x3f);mems(nx,0x3f);for(int i=0;i<=n;i++)v[i].clear(),s[i].clear();
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read(),v[a[i]].eb(i);
    for(int i=1;i<=n;i++)   r[i]=read();
    for(int i=1;i<=n;i++)   b[i]=read();
    a[n+1]=0;
    for(int i=n;i;i--){
        nx[i]=buc[a[i]];buc[a[i]]=i;
        R[i]=r[i];
        while(!s[a[i]].empty()&&s[a[i]].back()<=r[i]+1)  gmx(R[i],R[s[a[i]].back()]),s[a[i]].pop_back();
        while(!s[a[i]].empty()&&R[s[a[i]].back()]<=R[i]) s[a[i]].pop_back();
        s[a[i]].eb(i);
    }
    sf[n+2]=0;sf[n+1]=f[n+1]=1;
    for(int i=n;i;i--){
        f[i]=sf[i+1]-sf[R[i]+2];
        if(nx[i]<=R[i]+1){
            f[i]-=SF[nx[i]];
            int k=upper_bound(v[a[i]].begin(),v[a[i]].end(),R[i]+1)-v[a[i]].begin();
            if(k<v[a[i]].size())    f[i]+=SF[v[a[i]][k]];
        }
        sf[i]=sf[i+1]+f[i];
        SF[i]=(nx[i]<=n?SF[nx[i]]:mit(0))+f[i];
    }
    int l=1;mit ans=0;
    for(int i=1;i<=n;i++){
        if(a[l]<b[i]&&a[i+1]!=a[l])   ans+=f[i+1];
        if(a[i+1]<b[i]&&i<R[l]){
            ans+=sf[i+2]-sf[R[l]+2];
            int k=lower_bound(v[a[l]].begin(),v[a[l]].end(),i+2)-v[a[l]].begin();
            if(k<v[a[l]].size()&&v[a[l]][k]<=R[l]+1){
                ans-=SF[v[a[l]][k]];
                k=upper_bound(v[a[l]].begin(),v[a[l]].end(),R[l]+1)-v[a[l]].begin();
                if(k<v[a[l]].size())    ans+=SF[v[a[l]][k]];
            }
            // for(int j=i+2;j<=R[l]+1;j++)if(a[j]==a[l])ans-=f[j];
        }
        if(a[i+1]==b[i]){
            if(i+1>R[l])    break;
        }
        else if(b[i]==a[l]) l=i+1;
        else    break;
    }
    printf("%d\n",ans);
}
int main(){freopen("shuffle.in","r",stdin);freopen("shuffle.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}