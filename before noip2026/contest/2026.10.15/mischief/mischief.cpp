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
const int maxn=1010;
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
int n;
int a[maxn][maxn];
pii b[maxn*maxn];
unordered_set<int> v[maxn];
vector<vector<int>> ans;
void slv(int x1,int y1,int x2,int y2){
    if(x1==x2&&y1==y2)  return;
    ans.eb(vector<int>{x1,y1,x2,y2});
    swap(b[a[x1][y1]],b[a[x2][y2]]);
    swap(a[x1][y1],a[x2][y2]);
}
bool mem2;
int main(){
    // freopen("mischief.in","r",stdin);freopen("mischief.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=read(),b[a[i][j]]=pii(i,j);
    for(int i=1;i<=n;i++){
        int l=(i-1)*n+1,r=i*n;
        for(int j=l;j<=r;j++){
            int x=b[j].fi,y=b[j].se;
            v[y].ep(j);
        }
        queue<int> emp;while(!emp.empty())emp.pop();
        for(int j=1;j<=n;j++)if(v[j].empty())emp.ep(j);
        while(!emp.empty()){
            int u=emp.front();emp.pop();
            int p=l+u-1,x=b[p].fi,y=b[p].se;
            slv(x,y,i,y);slv(i,y,i,u);
            v[y].erase(p);if(v[y].empty())emp.ep(y);
        }
        for(int j=1;j<=n;j++)if(!v[j].empty()){
            // assert(v[j].size()==1);
            int p=*v[j].begin(),x=b[p].fi,y=b[p].se;
            slv(x,y,i,y);
        }
        for(int j=1;j<=n;j++)if(!v[j].empty()){
            // assert(v[j].size()==1);
            int p=*v[j].begin(),x=b[p].fi,y=b[p].se;
            slv(x,y,i,(p-1)%n+1);
            v[j].clear();
        }
    }
    print(ans.size(),'\n');
    for(auto i:ans){
        for(int j:i)print(j,' ');putc('\n');
    }
    Flush();
}