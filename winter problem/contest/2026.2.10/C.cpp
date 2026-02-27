#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10,maxv=7000,V=6561,bs=3;
bool mem1;
int n,cc;
int a[maxn],s[maxn][10];
int b[10],c[10],tmp[10];
int pq[10];
vector<int> v[maxv],vec[maxn];
int mp[maxv][10],buc[maxn];
// inline int hsh(int* h){int H=0;for(int i=8;i;i--)H+=(h[i]%3)*pq[i-1];return H;}
inline int hsh(int* h){int H=0;for(int i=8;i;i--)H=H*3+(h[i]%3);return H;}
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
void matt(int _cases){
    for(int i=0;i<V;i++)vector<int>().swap(v[i]);
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++){
        for(int j=0;j<10;j++)s[i][j]=s[i-1][j];
        s[i][a[i]]++;
        v[hsh(s[i])].eb(i);
    }
    debug("cnt = %d\n",cc);
    ll ans=0;int all=0;
    for(int _=1;_<=cc;_++){
        for(int i=1;i<=8;i++){
            c[i]=0;
            for(int j=max(i-2,1);j<=min(6,i);j++)c[i]+=mp[_][j];
        }
        ull H=hsh(c);for(int i=1;i<=8;i++)tmp[i]=c[i]%3;
        for(int i=1,j=1;i<=n;i++){
            j=max(j,i);
            while(j<=n){
                bool flag=true;
                for(int k=1;k<=8;k++)if(s[j][k]-s[i-1][k]<c[k]){flag=false;break;}
                if(flag)    break;
                j++;
            }
            if(j>n) break;
            if(i^1){
                if(tmp[a[i-1]]<2)   H+=pq[a[i-1]-1],tmp[a[i-1]]++;
                else    H-=pq[a[i-1]-1]*2,tmp[a[i-1]]=0;
            }
            vec[H].eb(j);all++;
        }
    }
    for(int i=0;i<V;i++){
        if(v[i].empty())    vector<int>().swap(vec[i]);
        if(vec[i].empty())  continue;
        for(int j:vec[i])   buc[j]++;vector<int>().swap(vec[i]);
        for(int j=1;j<=n;j++)   buc[j]+=buc[j-1];
        for(int j:v[i]) ans+=buc[j];
        mems(buc,0);
    }
    debug("all = %d\n",all);
    printf("%lld\n",ans);
}
void dfs(int x){
    if(x>6){
        b[7]=b[8]=0;
        ull H=hsh(b);memc(mp[H],b);cc++;
        return;
    }
    b[x]=0;dfs(x+1);
    b[x]=1;dfs(x+1);
    b[x]=2;dfs(x+1);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    pq[0]=1;for(int i=1;i<10;i++)pq[i]=pq[i-1]*bs;dfs(1);
    int T=read();for(int i=1;i<=T;i++)matt(i);
}