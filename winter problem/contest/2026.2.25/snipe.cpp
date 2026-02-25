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
const int maxn=5e5+10,BS=(1<<20)-1;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char ch){if(!x)return putc(48),putc(ch),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(ch);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
int n,mxc;
struct node{int a,b,c;}a[maxn];
priority_queue<ll,vector<ll>,greater<ll>> q1,q2;
bool vis[maxn];
int A[maxn],B[maxn],C[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
bool check(ll x){
    x<<=1;
    memset(vis,0,sizeof(bool)*(n+5));
    priority_queue<ll,vector<ll>,greater<ll>>().swap(q1);
    priority_queue<ll,vector<ll>,greater<ll>>().swap(q2);
    ll ma,mb,mc;int cnt=0,p=1,pa=1,pb=1,pc=1;
    while(cnt^n){
        while(vis[A[pa]])pa++;
        while(vis[B[pb]])pb++;
        while(vis[C[pc]])pc++;
        ma=a[A[pa]].a+x;mb=a[B[pb]].b+x;mc=a[C[pc]].c+x;
        while(p<=n&&a[p].a<=ma){
            if(a[p].b<=mb)  q1.ep(((ll)a[p].c<<20)|p);
            else    q2.ep(((ll)a[p].b<<20)|p);
            p++;
        }
        while(!q2.empty()){int t=q2.top()&BS;if(a[t].b<=mb){q2.pop();q1.ep(((ll)a[t].c<<20)|t);}else break;}
        if(q1.empty()||(q1.top()>>20)>mc)   return false;
        while(!q1.empty()){
            int t=q1.top()&BS;
            if(a[t].c<=mc){cnt++;q1.pop();vis[t]=true;}
            else    break;
        }
    }
    return true;
}
void matt(int _cases){
    n=read();int mx=0;
    for(int i=1;i<=n;i++){
        a[i].a=read(),a[i].b=read(),a[i].c=read();
        gmx(mx,abs(a[i].a)),gmx(mx,abs(a[i].b)),gmx(mx,abs(a[i].c));
    }
    sort(a+1,a+n+1,[&](node x,node y){return x.a<y.a;});
    iota(A+1,A+n+1,1);iota(B+1,B+n+1,1);iota(C+1,C+n+1,1);
    sort(A+1,A+n+1,[&](int x,int y){return a[x].a<a[y].a;});
    sort(B+1,B+n+1,[&](int x,int y){return a[x].b<a[y].b;});
    sort(C+1,C+n+1,[&](int x,int y){return a[x].c<a[y].c;});
    // if(spB::check())  return spB::solve();
    int l=0,r=mx,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
}
int main(){freopen("snipe.in","r",stdin);freopen("snipe.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}