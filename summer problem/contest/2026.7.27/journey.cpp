#pragma GCC optimize(2, 3, "Ofast")
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
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1010,maxm=2e5+10,maxq=1e6+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
int n,m,q;
pii E[maxm];
int f[maxn];
struct ques{int l,r,s,t;}Q[maxq];
bool ans[maxq];
vector<int> vq[maxn];
int vec[maxq],vl;
int main(){
    // freopen("journey.in","r",stdin);freopen("journey.out","w",stdout);
    n=read();m=read();q=read();
    for(int i=1;i<=m;i++)   E[i]=pii(read(),read());
    for(int i=1;i<=q;i++){
        int l=read(),r=read(),s=read(),t=read();
        Q[i]={l,r,s,t};
        if(s==t)    ans[i]=true;
        else    vq[s].eb(i);
    }
    for(int s=1;s<=n;s++){
        vl=0;
        for(int i:vq[s])    vec[++vl]=i;
        sort(vec+1,vec+vl+1,[&](int x,int y){return Q[x].r<Q[y].r;});
        mems(f,0);
        for(int i=1,k=1;k<=vl;i++){
            auto [u,v]=E[i];
            if(u==s)    f[v]=i;
            else if(v==s)   f[u]=i;
            else    gmx(f[u],f[v]),gmx(f[v],f[u]);
            while(k<=vl&&Q[vec[k]].r==i)    ans[vec[k]]=f[Q[vec[k]].t]>=Q[vec[k]].l,k++;
            while(k<=vl&&f[Q[vec[k]].t]>=Q[vec[k]].l)   ans[vec[k++]]=true;
        }
    }
    for(int i=1;i<=q;i++)   pus(ans[i]?"Yes\n":"No\n");
    Flush();
}