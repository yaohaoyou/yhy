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
const int maxn=2e5+10;
int n;
int a[maxn],b[maxn],c[maxn];
vector<pii> dp[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
inline int f(int r,int l){auto it=lower_bound(dp[r].begin(),dp[r].end(),pii(l,0));return it==dp[r].end()?0:it->se;}
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
vector<pii> v,tmp;
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        int x=read(),y=read();
        c[x]=y;c[y]=x;
    }
    dp[0].eb(1,0);
    for(int i=1;i<=n+n;i++){
        dp[i]=dp[i-1];
        if(c[i]<i){
            // dp[i][l]=dp[i-1][c[i]+1]+1+dp[c[i]-1][l]
            vector<pii>().swap(tmp);vector<pii>().swap(v);
            int F=f(i-1,c[i]+1);
            for(auto [l,j]:dp[c[i]-1])  tmp.eb(l,F+1+j);
            tmp.eb(c[i],F+1);
            // printf("F = %d\n",F);
            // printf("tmp : ");for(auto [i,j]:tmp) printf("%d %d\n",i,j);puts("");
            // printf("dp : ");for(auto [i,j]:dp[i]) printf("%d %d\n",i,j);puts("");
            v.resize(dp[i].size()+tmp.size());
            merge(tmp.begin(),tmp.end(),dp[i].begin(),dp[i].end(),v.begin());
            int lst=-1;
            reverse(v.begin(),v.end());
            int mx=0;vector<pii>().swap(dp[i]);
            for(pii j:v)if((mx=max(mx,j.se))^lst)dp[i].eb(j.fi,lst=mx);
            reverse(dp[i].begin(),dp[i].end());
        }
        // for(auto [l,j]:dp[i]) printf("%d %d : %d\n",l,i,j);
    }
    printf("%d\n",f(n+n,1));
}