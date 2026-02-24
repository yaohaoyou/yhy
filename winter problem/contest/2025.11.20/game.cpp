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
const int maxn=1e6+100,maxp=maxn*4,lg=20,inf=1e9;
bool mem1;
int n,k,tot;
int a[maxn];
int nx[maxp],pr[maxp];
struct node{int l,r,c;}b[maxp];
int lst[maxn];
int v1[maxp],v2[maxp],v[maxp];
int l1,l2;
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
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
bool mem2;
inline int nd(node x){int p=++tot;b[p]=x;nx[p]=inf;pr[p]=0;return p;}
void matt(int _cases){
    n=read();k=read();
    tot=0;mems(lst,0);
    for(int i=1;i<=n+lg;i++)    lst[i]=nd({-1,-1,0});
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++){
        int j=i;while(j<=n&&a[i]==a[j])j++;j--;
        int p=nd({i,j,j-i+1});pr[p]=lst[a[i]];nx[p]=inf;nx[pr[p]]=p;
        lst[a[i]]=p;i=j;
    }
    int ans=0;
    for(int o=1;o<=n+lg;o++){
        l1=l2=0;
        int p=o;
        while(p^inf){
            int l=b[p].l,r=b[p].r,c=b[p].c,nxx=nx[p];
            if(c)   ans=o;
            if(!c&&b[v1[l1]].c)  v1[++l1]=p;
            if(c>=k){
                if(c%k==0)  b[p].c/=k,v1[++l1]=p;
                else{
                    int x=nd({l,r-1,c/k}),y=p,z=nd({l+1,r,c/k});
                    b[p].c=0;
                    nx[x]=y;pr[y]=x;nx[y]=z;pr[z]=y;
                    v1[++l1]=x;v1[++l1]=y;v1[++l1]=z;
                }
            }
            p=nxx;
        }
        if(ans!=o)  l1=0;
        if(o==n+lg) break;
        p=o+1;for(;p!=inf;p=nx[p])v2[++l2]=p;
        merge(v1+1,v1+l1+1,v2+1,v2+l2+1,v+1,[&](int x,int y){return b[x].l!=b[y].l?b[x].l<b[y].l:b[x].r<b[y].r;});
        int ls=0;
        for(int i=1;i<=l1+l2;i++){
            int x=v[i],j=i+1,c=b[x].c;
            if(c){while(j<=l1+l2&&b[v[j]].c&&b[v[j]].l==b[v[j-1]].r+1)c+=b[v[j]].c,j++;}
            j--;
            b[x].r=b[v[j]].r;b[x].c=c;
            pr[x]=ls;nx[ls]=x;ls=x;
            i=j;
        }
        nx[ls]=inf;
    }
    printf("%d\n",ans);
}
int main(){freopen("game.in","r",stdin);freopen("game.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T=read();for(int i=1;i<=T;i++)matt(i);}