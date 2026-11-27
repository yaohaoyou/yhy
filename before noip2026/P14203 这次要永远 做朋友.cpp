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
const int maxn=3e6+10;
int n;
int a[maxn],b[maxn],mp[maxn<<1],nx[maxn],pr[maxn],p[maxn],s[maxn];
ll ans;
void dvd(int l,int r){
    if(l==r)    return ans+=!a[l],void();
    int mid=(l+r)>>1;
    auto clr=[&](){for(int i=l;i<=r;i++)b[a[i]]=0;};
    clr();for(int i=r;i>=l;i--){nx[i]=b[a[i]];b[a[i]]=i;}
    clr();for(int i=l;i<=r;i++){pr[i]=b[a[i]];b[a[i]]=i;}
    set<int> v;
    int mx=0;
    clr();
    for(int i=mid;i>=l;i--){
        b[a[i]]++;if(b[a[i]]>b[mx])mx=a[i];
        if(b[mx]*2>mid-i+1) v.ep(mx);
    }
    clr();
    int j=l;
    for(int c:v){
        if(c>(r-l+1)/2)   break;
        int cnt=count(b,b+c,1);
        while(j<=r&&cnt<c){
            if(a[j]<c&&!b[a[j]])    cnt++;
            b[a[j]]=1;j++;
        }
        if(cnt<c)   break;
        s[l-1]=0;
        for(int i=l;i<=r;i++){
            s[i]=s[i-1]+2*(a[i]==c)-1;
            if(i>mid)   mp[s[i]+n]++;
        }
        int nw=mid+1,sum=0,now=0;
        for(int x=now;x<=r-l+1;x++) sum+=mp[x+n];
        for(int i=l,k=max(j-1,mid+1);i<=mid;i++){
            while(nw<k){
                if(s[nw]>=now)   sum--;
                mp[s[nw++]+n]--;
            }
            if(s[mid]>s[i-1]){
                while(now>s[i-1]+1) now--,sum+=mp[now+n];
                while(now<s[i-1]+1) sum-=mp[now+n],now++;
                ans+=sum;
                // for(int x=s[i-1]+1;x<=r-l+1;x++)  ans+=mp[x+n];//,printf("add%d [%d,%d] %d %d %d\n",c,i,k,x,mp[x+n],s[r]);
            }
            if(a[i]<c){
                if(nx[i])   gmx(k,nx[i]);
                else    break;
            }
        }
        while(nw<=r)    mp[s[nw++]+n]=0;
    }
    mx=0;
    clr();v.clear();
    for(int i=mid+1;i<=r;i++){
        b[a[i]]++;if(b[a[i]]>b[mx])mx=a[i];
        if(b[mx]*2>i-mid)   v.ep(mx);
    }
    clr();
    j=r;
    for(int c:v){
        if(c>(r-l+1)/2)   break;
        int cnt=count(b,b+c,1);
        while(j>=l&&cnt<c){
            if(a[j]<c&&!b[a[j]])    cnt++;
            b[a[j]]=1;j--;
        }
        if(cnt<c)   break;
        s[r+1]=0;
        for(int i=r;i>=l;i--){
            s[i]=s[i+1]+2*(a[i]==c)-1;
            if(i<=mid&&s[i]<=s[mid+1])  mp[s[i]+n]++;
        }
        int nw=mid,sum=0,now=0;
        for(int x=now;x<=r-l+1;x++) sum+=mp[x+n];
        for(int i=r,k=min(j+1,mid);i>mid;i--){
            while(nw>k){
                if(s[nw]<=s[mid+1]){
                    mp[s[nw]+n]--;
                    if(s[nw]>=now)      sum--;
                }
                nw--;
            }
            if(s[mid+1]>s[i+1]){
                while(now>s[i+1]+1) now--,sum+=mp[now+n];
                while(now<s[i+1]+1) sum-=mp[now+n],now++;
                ans+=sum;
                // for(int x=s[i+1]+1;x<=r-l+1;x++)  ans+=mp[x+n];//,printf("add%d [%d,%d] %d %d %d\n",c,k,i,x,mp[x+n],s[l]);
            }
            if(a[i]<c){
                if(pr[i])   gmn(k,pr[i]);
                else    break;
            }
        }
        while(nw>=l)    mp[s[nw--]+n]=0;
    }
    clr();
    dvd(l,mid);dvd(mid+1,r);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int c=0;c<=n;c++){
        
    }
    dvd(1,n);
    printf("%lld\n",ans);
}