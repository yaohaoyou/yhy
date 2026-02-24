#pragma GCC optimize(2,3,"Ofast")
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define piiii pair<pii,pii>
#define pqi priority_queue<int,vector<int>,greater<int>>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2.5e5+10,B=510;
int n,m,cnt=0;
int lst[B][B];
vector<piii> W;
vector<int> out[maxn],a[maxn],ans[maxn];
vector<int> ins[B],era[B];
vector<int> v[maxn];
vector<int> mp[maxn];
unordered_set<int> bef;
pqi q1,q2;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
inline void gmn(int &x,int y){(x>y)&&(x=y);}
void matt(int _cases){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        mp[i].resize(m+1);
        for(int j=1;j<=m;j++)  mp[i][j]=getc()-'0';
        getc();
    }
    bool flag=false;
    if(n>m){
        swap(n,m);
        for(int i=1;i<=n;i++)   a[i].resize(m+1),ans[i].resize(m+1);
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=mp[j][n-i+1];
        flag=true;
    }
    else{
        for(int i=1;i<=n;i++)   a[i].resize(m+1),ans[i].resize(m+1);
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=mp[i][j];
    }
    pqi().swap(q1);pqi().swap(q2);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)ans[i][j]=1e9;
    for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)lst[i][j]=0;
    for(int i=1;i<=n;i++){
        cnt=0;W.clear();
        for(int k=1;k<=m;k++){
            unordered_set<int>().swap(bef);
            bool flag=true;
            for(int j=i+1;j<=n;j++){
                if(a[i][k]&&a[j][k]){
                    if(lst[i][j]&&bef.find(lst[i][j])==bef.end()){
                        int w=(j-i+1)*(k-lst[i][j]+1);
                        for(int l=lst[i][j];l<=k;l++)W.eb(piii(w,pii(i,j))),v[l].eb(cnt++);
                        bef.ep(lst[i][j]);
                    }
                    lst[i][j]=k;
                }
            }
        }
        for(int k=1;k<=m;k++){
            for(int j:v[k])    ins[W[j].se.fi].eb(W[j].fi),era[W[j].se.se+1].eb(W[j].fi);
            vector<int>().swap(v[k]);
            for(int j=1;j<=n+1;j++){
                for(int k:ins[j])    q1.ep(k);
                for(int k:era[j])    q2.ep(k);
                while(!q1.empty()&&!q2.empty()&&q1.top()==q2.top()) q1.pop(),q2.pop();
                ins[j].clear();era[j].clear();
                if(!q1.empty()) gmn(ans[j][k],q1.top());
            }
        }
    }
    if(flag){
        swap(n,m);
        for(int i=1;i<=n;i++)   out[i].resize(m+1);
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)out[i][j]=ans[m-j+1][i];
    }
    else{
        for(int i=1;i<=n;i++)   out[i].resize(m+1);
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)out[i][j]=ans[i][j];
    }
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++)printf("%d ",out[i][j]==1e9?0:out[i][j]);
    for(int i=1;i<=n;i++)vector<int>().swap(out[i]),vector<int>().swap(mp[i]),vector<int>().swap(a[i]),vector<int>().swap(ans[i]);
}
int main(){int T=read();for(int i=1;i<=T;i++)matt(i);}