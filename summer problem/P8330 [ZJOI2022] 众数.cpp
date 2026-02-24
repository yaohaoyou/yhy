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
#define if(sth) if(__builtin_expect(sth,1))
using namespace std;
const int maxn=2e5+10,B=256;
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
int n;
int tot;
int a[maxn],s[maxn],col[maxn],f[maxn];
vector<int> v[maxn];
vector<int> ans;int out;
unordered_map<int,int> id;
void solve(){
    mems(f,0);
    for(int i=1;i<=n;i++){
        if(v[id[a[i]]].size()>B)    continue;
        int x=id[a[i]],k=lower_bound(v[x].begin(),v[x].end(),i)-v[x].begin()+1,c=0;
        {
            int res=v[x].size()-k+1+f[1];
            if(res>out) ans.clear(),out=res;
            if(res==out)    ans.eb(a[i]);
        }
        for(int j:v[x]){
            if(j>i) break;
            c++;
            int res=v[x].size()-k+1+c+f[j+1];
            if(j==i)    res--;
            if(res>out) ans.clear(),out=res;
            if(res==out)    ans.eb(a[i]);
        }
        c=0;
        for(int j:v[x]){
            if(j>i) break;
            c++;
            int p=j;
            while(p&&f[p]<k-c+1)    f[p]=k-c+1,p--;
        }
    }
}
void matt(){
    for(int i=1;i<=tot;i++)v[i].clear();tot=out=0;ans.clear();
    id.clear();
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(id.find(a[i])==id.end()) id[a[i]]=++tot,col[tot]=a[i];
        v[id[a[i]]].eb(i);
    }
    for(int i=1;i<=tot;i++){
        if(v[i].empty())    continue;
        int x=a[v[i][0]];
        if(v[i].size()>B){
            for(int j=1;j<=n;j++)   s[j]=s[j-1]+(a[j]==x);
            for(int j=1;j<=tot;j++){
                int mx=-1e9,c=0,res=0;
                for(int k:v[j]){
                    c++;
                    res=max(res,s[k-1]-c+1+int(v[j].size())+mx);
                    mx=max(mx,c-s[k]);
                }
                if(res>out) ans.clear(),out=res;
                if(res==out)    ans.eb(col[j]);
            }
            for(int j=1;j<=tot;j++){
                int mx=-1e9,c=0,res=0;
                for(int k:v[j]){
                    c++;
                    res=max(res,s[n]-s[k]+c+mx);
                    mx=max(mx,s[k-1]-c+1);
                }
                if(res>out) ans.clear(),out=res;
                if(res==out)    ans.eb(col[i]);
            }
        }
    }
    solve();
    reverse(a+1,a+n+1);
    for(int i=1;i<=tot;i++){for(int &j:v[i])j=n-j+1;reverse(v[i].begin(),v[i].end());}
    solve();
    sort(ans.begin(),ans.end());ans.erase(unique(ans.begin(),ans.end()),ans.end());
    printf("%d\n",out);
    for(int i:ans)  printf("%d\n",i);
}
int main(){int T=read();while(T--)matt();}