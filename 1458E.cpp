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
const int maxn=2e6+10,inf=2e9;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
int n,q;
pii Q[maxn];
struct node{
    int fi,se,id;
    bool operator<(node y){return pair<pii,int>(pii(fi,se),id)<pair<pii,int>(pii(y.fi,y.se),y.id);}
}a[maxn];
set<pii> odt;
bool ans[maxn];
unordered_map<int,int> sx,sy;
void ins(int x){
    auto it=odt.lower_bound(pii(x,inf));
    if(it!=odt.begin()){it--;if(it->fi<=x&&x<=it->se)return;}
    int l=x,r=x;
    auto itl=odt.ep(x,x).fi,itr=itl;
    while(itl!=odt.begin()){itl--;if(itl->se==l-1)l=itl->fi;else{itl++;break;}}
    while((++itr)!=odt.end()){if(itr->fi==r+1)r=itr->se;else break;}
    odt.erase(itl,itr);
    odt.ep(l,r);
}
int main(){
    // freopen("act.in","r",stdin);freopen("act.out","w",stdout);
    n=read();q=read();
    // for(int i=1;i<=n;i++)   a[i].fi=read();
    // for(int i=1;i<=n;i++)   a[i].se=read();
    for(int i=1;i<=n;i++)   a[i]={read(),read(),0};
    a[++n]={0,0,0};
    for(int i=1;i<=n;i++){
        if(sx.find(a[i].fi)==sx.end()) sx[a[i].fi]=a[i].se;
        else    gmn(sx[a[i].fi],a[i].se);
        if(sy.find(a[i].se)==sy.end()) sy[a[i].se]=a[i].fi;
        else    gmn(sy[a[i].se],a[i].fi);
    }
    mems(ans,true);
    for(int i=1;i<=q;i++){
        int x=read(),y=read();
        a[++n]={x,y,i};
        Q[i]=pii(x,y);
    }
    sort(a+1,a+n+1);
    int sx=0,sy=0;
    for(int i=1;i<=n;i++){
        int k=i,p=0;while(k<=n&&a[k].fi==a[i].fi)k++;k--;
        for(int j=i;j<=k;j++)if(!a[j].id){p=j;break;}
        int x=sx,y=sy;
        // y+=a[i].fi-x;x=a[i].fi;
        for(auto it=odt.lower_bound(pii(y,inf));it!=odt.end();it++){
            x+=it->fi-y,y=it->fi;
            if(x<a[i].fi){
                y=it->se+1;
                if(sx<=x)    sx=x,sy=y;
            }
            else    break;
        }
        x=sx;y=sy;
        y+=a[i].fi-x;x=a[i].fi;
        if(p&&y>=a[p].se){  // a[i].fi,y=true
            for(int j=i;j<=k;j++)if(!a[j].id)ins(a[j].se);
            x++;auto it=odt.lower_bound(pii(y,inf));
            if(it!=odt.begin()){
                it--;
                if(it->fi<=y&&it->se>=y)    y=it->se+1;
            }
            // for(auto [l,r]:odt)printf("[%d,%d] ",l,r);puts("");
            // printf("ep2 %d %d\n",x,y);
            sx=x,sy=y;
        }
        else{
            auto it=odt.lower_bound(pii(y,inf));
            if(it!=odt.begin()){
                it--;
                if(it->fi<=y&&it->se>=y)    y=it->se+1;
            }
            // printf("ep3 %d %d\n",x,y);
            sx=x,sy=y;
            for(int j=i;j<=k;j++)if(!a[j].id)ins(a[j].se);
        }
        {
            int x=sx,y=sy;
            // printf("%d %d\n",x,y);
            for(int j=i;j<=k;j++)   ans[a[j].id]=y+a[j].fi-x!=a[j].se;
        }
        i=k;
    }
    for(int _cases=1;_cases<=q;_cases++){
        int x=Q[_cases].fi,y=Q[_cases].se;
        node z=*lower_bound(a+1,a+n+1,(node){x,y,0});
        if(z.fi==x&&z.se==y&&z.id==0) pus("LOSE\n");
        else if((::sx.find(x)!=::sx.end()&&::sx[x]<y)||(::sy.find(y)!=::sy.end()&&::sy[y]<x))    pus("WIN\n");
        else pus(ans[_cases]?"WIN\n":"LOSE\n");
    }
    FastIO::flush();
}