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
const int maxn=2e6+10,maxT=1e6+10;
int n,m;
bool ans[maxT];
vector<pii> Q[maxn];
// bitset<maxn> dp[maxn];  // dp[i][j] 表示剩 i 个球，上一步选择 j，当前选手是否必胜
int f[maxn];
void ques(){
    vector<pii> v;
    for(int i=1;i<=10000;i++)for(int j=1;j<=10000;j++)v.eb(i,j);
    printf("%d\n",v.size());for(auto [i,j]:v)printf("%d %d\n",i,j);
    exit(0);
}
int T;
int main(){
    // ques();
    freopen("collect.in","r",stdin);freopen("collect.out","w",stdout);
    T=read();
    for(int i=1;i<=T;i++){
        n=read();m=read();
        if(!(m&1))  ans[i]=n%(m+1);
        else    Q[m].eb(n,i);
    }
    for(m=1;m<=10000;m+=2){
        if(Q[m].empty())    continue;
        n=max_element(Q[m].begin(),Q[m].end())->fi;
        mems(f,-1);
        f[m+m]=m;
        for(int i=m+1;i<=n;i++){
            for(int j=m;~j;j--){
                if((!~f[i])||(f[i]==j)){
                    if(~f[i+j]) f[i+j]=-2;
                    else    f[i+j]=j;
                }
            }
        }
        for(auto [i,j]:Q[m])    ans[j]=i<=m?1:((~f[i])&&f[i]);
    }
    for(int i=1;i<=T;i++){
        puts(ans[i]?"YES":"NO");
        // if(!ans[i]) printf("%d %d\n",qq[i].fi,qq[i].se);
    }
}