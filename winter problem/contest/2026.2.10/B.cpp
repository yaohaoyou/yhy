#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
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
const int maxn=2048+10,B=256;
bool mem1;
int n;
int a[maxn][maxn];
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
inline ll H(int x,int y){return 1ll*x*n+y;}
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int id[maxn][maxn],tot;
ll dp[maxn],dp2[maxn];
__gnu_pbds::cc_hash_table<ll,ll> f[maxn<<1],fl[maxn<<1],fr[maxn<<1];
bool mem2;
int main(){
    // freopen("C:\\Users\\User\\Downloads\\ex_26TG04T2_test\\ex_26TG04T2_test5.in","r",stdin);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=read();
    for(int len=1;len<=B;len<<=1)for(int i=1,j=len;i<=n;i+=len,j+=len)id[i][j]=++tot;
    for(int i=1;i<n;i++)fr[id[i][i]][H(i,i+1)]=a[i][i+1];
    for(int i=2;i<=n;i++)fl[id[i][i]][H(i,i-1)]=a[i][i-1];
    for(int len=2;len<=B;len<<=1){
        debug("len = %d\n",len);
        for(int l=1,r=len;l<=n;l+=len,r+=len){
            int mid=(l+r)>>1,k=id[l][r],kl=id[l][mid],kr=id[mid+1][r];
            for(int i=l;i<=r;i++)for(int j=l;j<=r;j++)f[k][H(i,j)]=1e18;
            for(int i=l;i<=mid;i++){
                for(int p=mid+1;p<=r;p++){
                    for(int q=mid+1;q<=r;q++)   gmn(f[k][H(i,q)],fr[kl][H(i,p)]+f[kr][H(p,q)]);
                    for(int j=l;j<=mid;j++) gmn(f[k][H(p,j)],f[kl][H(i,j)]+fl[kr][H(p,i)]);
                }
            }
            if(len^B){
                if(l^1){
                    for(int i=l;i<=r;i++)for(int j=l-len;j<=r-len;j++){
                        fl[k][H(i,j)]=1e18;
                        for(int o=l;o<=r;o++)gmn(fl[k][H(i,j)],f[k][H(i,o)]+a[o][j]);
                    }
                }
                if(r^n){
                    for(int i=l;i<=r;i++)for(int j=l+len;j<=r+len;j++){
                        fr[k][H(i,j)]=1e18;
                        for(int o=l;o<=r;o++)gmn(fr[k][H(i,j)],f[k][H(i,o)]+a[o][j]);
                    }
                }
            }
        }
    }
    if(n<=B){
        ll ans=1e18;for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)gmn(ans,f[id[1][n]][H(i,j)]);
        printf("%lld\n",ans);
        return 0;
    }
    vector<pii> v;
    {
        int i=1,N=n/B;
        while(N^1){
            for(int j=1,k=1;j<=i;j++,k+=N)   v.eb(k-1,N);
            i<<=1;N>>=1;
        }
    }
    debug("sz = %d\n",v.size());
    ll ans=1e18;
    vector<pii> vec;
    for(int s=0;s<(1<<v.size());s++){
        vec.clear();
        for(int l=1,r=B;l<=n;l+=B,r+=B) vec.eb(l,r);
        for(int i=0;i<v.size();i++)
            if(s&(1<<i))for(int j=v[i].fi;j<v[i].fi+(v[i].se/2);j++)swap(vec[j],vec[j+(v[i].se/2)]);
        {
            mems(dp,0x3f);mems(dp2,0x3f);
            {
                auto [l,r]=vec.front();
                for(int i=l;i<=r;i++)for(int j=l;j<=r;j++)gmn(dp[j],f[id[l][r]][H(i,j)]);
            }
            for(int i=1;i<vec.size();i++){
                auto [l,r]=vec[i];auto [pl,pr]=vec[i-1];
                for(int j=pl;j<=pr;j++)for(int k=l;k<=r;k++)gmn(dp2[k],dp[j]+a[j][k]);
                for(int k=l;k<=r;k++)for(int p=l;p<=r;p++)gmn(dp[p],dp2[k]+f[id[l][r]][H(k,p)]);
            }
            {
                auto [l,r]=vec.back();
                for(int i=l;i<=r;i++)   gmn(ans,dp[i]);
            }
        }
    }
    printf("%lld\n",ans);
}