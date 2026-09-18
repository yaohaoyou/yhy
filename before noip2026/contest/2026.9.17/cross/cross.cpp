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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e6+10;
int n;
int a[maxn],b[maxn],pre[maxn];
int p[maxn];
struct st{
    int Log[maxn];
    int st[20][maxn];
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=pre[i];
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    int query(int l,int r){int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
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
bool mem2;
void baoli(){
    ll s=0;
    for(int i=1;i<=n;i++)   s+=abs(a[i]-b[i]);
    iota(p+1,p+n+1,1);
    ll ans=0;
    do{
        ll w=0;
        for(int i=1;i<=n;i++)w+=abs(a[i]-b[p[i]]);
        if(w!=s)    continue;
        w=0;
        for(int i=1;i<=n;i++)for(int j=1;j<i;j++)w+=p[j]>p[i];
        if(w==5){
            for(int i=1;i<=n;i++)   printf("%d ",p[i]);puts("");
        }
        gmx(ans,w);
    }while(next_permutation(p+1,p+n+1));
    printf("%lld\n",ans);exit(0);
}
ll ans;
void solve(int l,int r,int L,int R){
    if(l>r||L>R)    return;
    // printf("%d %d %d %d\n",l,r,L,R);
    int pl=l+1,pr=r,i=l;
    while(pl<=pr){
        int mid=(pl+pr)>>1;
        if(st.query(l+1,mid)>=l-L+2)  i=mid,pl=mid+1;
        else    pr=mid-1;
    }
    ans+=i-l;
    int j=L-l+i;
    solve(l+1,i,L,j-1);solve(i+1,r,j+1,R);
    // for(int i=l,j=L;i<=r;i++,j++){
    //     if(i==r||a[i+1]>b[j]){
    //         ans+=i-l;
    //         solve(l+1,i,L,j-1);solve(i+1,r,j+1,R);
    //         break;
    //     }
    // }
}
int main(){
    freopen("cross.in","r",stdin);freopen("cross.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   b[i]=read();
    for(int i=1;i<=n;i++)if(a[i]>b[i])swap(a[i],b[i]);
    for(int i=1,j=0;i<=n;i++){
        while(j<n&&b[j+1]<a[i])    j++;
        pre[i]=i-j;
    }
    st.build();
    solve(1,n,1,n);printf("%lld\n",ans);
    // while(true){
    //     bool fl=false;
    //     for(int i=1;i<n;i++){
    //         if(a[i]<a[i+1]&&abs(a[i]-b[i])+abs(a[i+1]-b[i+1])==abs(a[i]-b[i+1])+abs(a[i+1]-b[i])){
    //             swap(a[i],a[i+1]);
    //             fl=true;
    //             // break;
    //         }
    //     }
    //     if(!fl) break;
    // }
    // ll ans=0;for(int i=1;i<=n;i++)for(int j=1;j<i;j++)ans+=a[j]>a[i];printf("%lld\n",ans);return 0;
    // for(int i=1,j=0;i<=n;i++){
    //     if(b[i]<=a[i]){
    //         while(j<n&&b[j+1]<=a[i])    j++;
    //         R[1][i]=j;
    //     }
    // }
    // for(int i=1;i<=n;i++){
    //     int r=max(R[0][i],R[1][i]);
    //     for(int j=i;j<=r;j++)   gmx(f[j+1],f[i]+1ll*(j-i+1)*(j-i)/2);
    // }
    // printf("%lld\n",f[n]);
}