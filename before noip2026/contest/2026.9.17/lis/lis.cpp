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
const int maxn=2e5+10,maxq=5e5+10,B=600,maxV=1e6+10,LEN=100;
int V;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
    inline char gc(){char c=getc();while(c!='<'&&c!='>'&&c!='!')c=getc();return c;}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::gc;
int pos[maxV+10];
namespace SGT{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,maxV
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[(maxV+10)<<2][3];
    multiset<int> st[maxV+10][2];
    inline void pu(int p){tr[p][0]=max(tr[ls][0],tr[rs][0]);tr[p][1]=max(tr[ls][1],tr[rs][1]);tr[p][2]=max({tr[ls][2],tr[rs][2],tr[ls][0]+tr[rs][1]});}
    void build(setpos){tr[p][0]=tr[p][1]=tr[p][2]=0;if(l==r)return pos[l]=p,st[l][0].clear(),st[l][1].clear(),void();setmid;build(lson);build(rson);pu(p);}
    inline void ins(int x,bool o,int s){
        int p=pos[x];
        st[x][o].ep(s);
        if(tr[p][o]<s){tr[p][o]=s;while(p>>=1)pu(p);}
    }
    inline void del(int x,bool o,int s){
        int p=pos[x];
        st[x][o].erase(st[x][o].find(s));
        s=st[x][o].empty()?0:*(--st[x][o].end());
        if(tr[p][o]^s){tr[p][o]=s;while(p>>=1)pu(p);}
    }
    int query(setpos,int pl,int pr,bool o){if(l>=pl&&r<=pr)return tr[p][o];setmid,res=0;if(pl<=mid)res=query(lson,pl,pr,o);if(pr>mid)gmx(res,query(rson,pl,pr,o));return res;}
}
using namespace SGT;
int n,q,ps=1;
int a[maxn],f[2][maxn],id[maxn],bl[maxn],br[maxn],mv[maxn];
pii Q[maxq];
int now;
void era(int x,bool o){for(int i=bl[x];i<=br[x];i++)del(a[i],o,f[o][i]);}
void get(int x,bool o){
    int l=bl[x],r=br[x];
    if(!o){
        for(int i=l;i<=r;i++){
            f[0][i]=query(all,0,a[i]-1,0)+1;
            ins(a[i],0,f[0][i]);
        }
    }
    else{
        for(int i=r;i>=l;i--){
            f[1][i]=query(all,a[i]+1,maxV,1)+1;
            ins(a[i],1,f[1][i]);
        }
    }
}
vector<int> vec;
int buc[maxV];
int cnt=0;
void build(){
    cnt++;
    int l=bl[id[ps]],r=br[id[ps]];
    now=0;
    mems(buc,0);
    for(int i=r+1;i<=n;i++) gmx(buc[a[i]],f[1][i]);
    for(int i=maxV;i;i--)  gmx(buc[i],buc[i+1]);
    for(int i=1;i<l;i++)    gmx(now,f[0][i]+buc[a[i]+1]);
}
// int query(){
//     int l=bl[id[ps]],r=br[id[ps]],ans=now;
//     for(int i=l;i<=r;i++){
//         f[0][i]=T[0].query(all,0,a[i]-1)+1;
//         gmx(ans,f[0][i]+buc[a[i]+1]);
//         T[0].ins(a[i],f[0][i]);
//     }
//     for(int i=l;i<=r;i++)   T[0].del(a[i],f[0][i]);
//     return ans;
// }
// void build_block(){
    // int lst=0,bb=0,mn=1e9;
    // sort(vec.begin(),vec.end());
    // vec.erase(unique(vec.begin(),vec.end()),vec.end());
    // if(vec[0]!=1)   bl[++bb]=1,br[bb]=vec[0]-1;
    // for(int i=0;i<vec.size();i++){
    //     int r=vec.size()-1;
    //     for(int j=i;j<vec.size();j++)if(vec[j]-vec[i]>=LEN){r=j;break;}
        // int l=i,r=min(int(vec.size())-1,i+B-1);
    //     bb++;bl[bb]=br[bb-1]+1;br[bb]=vec[r];
    //     i=r;
    // }
    // if(vec.back()^n)    bl[++bb]=vec.back()+1,br[bb]=n;
    // for(int i=1;i<=n;i++){
    //     gmn(mn,mv[i]);
    //     if(i==n||i-lst+1>=LEN+LEN||(mn<=B&&i-lst+1>=LEN)){
    //         bl[++bb]=lst+1;br[bb]=lst=i;
    //         mn=1e9;
    //     }
    //     // if(i==n||i-lst>=B+B){
    //         // int x=min_element(mv+lst+1,mv+i+1)-mv;
    //         // bl[++bb]=lst+1;br[bb]=x;
    //         // lst=x;i=x;
    //     // }
    // }
    // for(int i=1;i<=bb;i++)for(int j=bl[i];j<=br[i];j++)id[j]=i;
    // debug("bb = %d\n",bb);
//     for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
//     for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,n);
// }
bool mem2;
int main(){
    freopen("lis.in","r",stdin);freopen("lis.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    V=*max_element(a+1,a+n+1);
    for(int i=1;i<=q;i++){
        char op=gc();
        if(op=='<') ps--,mv[ps]++,Q[i].fi=-1;
        else if(op=='>')    ps++,mv[ps]++,Q[i].fi=1;
        else    Q[i].se=read(),vec.eb(ps),gmx(V,Q[i].se);
    }
    V++;
    // for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    // for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,n);
    build(all);
    for(int i=n;i;i--){
        f[1][i]=query(all,a[i]+1,V,1)+1;
        ins(a[i],1,f[1][i]);
    }
    ps=1;
    bool flag=false;
    for(int _=1;_<=q;_++){
        if(Q[_].fi==-1){
            ps--;
            f[1][ps]=query(all,a[ps]+1,V,1)+1;
            ins(a[ps],1,f[1][ps]);
            del(a[ps],0,f[0][ps]);
        }
        else if(Q[_].fi==1){
            del(a[ps],1,f[1][ps]);f[1][ps]=0;
            f[0][ps]=query(all,0,a[ps]-1,0)+1;
            ins(a[ps],0,f[0][ps]);
            ps++;
        }
        else{
            del(a[ps],1,f[1][ps]);
            a[ps]=Q[_].se;
            f[1][ps]=query(all,a[ps]+1,V,1)+1;
            ins(a[ps],1,f[1][ps]);
            // for(int i=1;i<=n;i++)   printf("%d ",f[0][i]);puts("");
            // for(int i=1;i<=n;i++)   printf("%d ",f[1][i]);puts("");
            print(tr[1][2],'\n');
        }
    }
    // printf("cnt = %d\n",cnt);
    FastIO::flush();
}