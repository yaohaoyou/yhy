#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2.5e5+10;
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
int n,m[2],q;
pll Q[maxn];
pll a[2][maxn];
ll ans[maxn];
unordered_map<ll,queue<pli>> mv[2];
map<ll,int> mp[2],pos[2];
map<ll,vector<ll>> vid[2];
inline void era(bool o){
    ll x=mp[o].begin()->fi;
    for(ll i:vid[o][x]){
        pos[o][i]++;if(__int128(i)*pos[o][i]>1e12)  continue;
        while(!mv[o][i].empty()&&mv[o][i].front().fi<pos[o][i]){
            if(!o&&i==8)    debug("%d\n",mv[o][i].front().fi);
            mv[o][i].pop();
        }
        if(!mv[o][i].empty()){
            int nw=mv[o][i].front().se;
            mp[o][i*pos[o][i]]+=nw;
            vid[o][i*pos[o][i]].eb(i);
        }
    }
    mp[o].erase(mp[o].begin());vid[o].erase(vid[o].begin());
}
void abstract(){
    // n=read();q=read();
    // printf("%d %d\n",n,q);
    // for(int i=1;i<=n;i++){
    //     char op=getc();ll x,y;
    //     while(op!='L'&&op!='R') op=getc();x=readll();y=readll();
    //     printf("%c %lld %lld\n",op,x,y);
    // }
    q=100000;
    for(int i=1;i<=q;i++)   Q[i].fi=readll();
    for(int i=1;i<=q;i++)   Q[i].se=readll();
    sort(Q+1,Q+q+1);
    for(int i=1;i<=q;i++)   printf("%lld\n",Q[i].se);
    exit(0);
}
int main(){
    // freopen("pingpong.in","r",stdin);freopen("pingpong.out","w",stdout);
    // abstract();
    n=read();q=read();
    for(int i=1;i<=n;i++){
        char op=getc();ll x,y;
        while(op!='L'&&op!='R') op=getc();
        x=readll();y=readll();bool o=op=='R';
        a[o][++m[o]]=pll(x,y);
    }
    for(int o:{0,1}){
        int M=m[o];m[o]=0;
        sort(a[o]+1,a[o]+M+1);
        for(int i=1;i<=M;i++){
            ll len=a[o][i].fi;
            int j=i;while(j<=M&&a[o][j].fi==len)j++;j--;
            for(int k=i;k<=j;k++)   mv[o][len].ep(a[o][k].se,j-k+1);
            pos[o][len]=1;
            mp[o][len]+=mv[o][len].front().se;
            vid[o][len].eb(len);
            i=j;
        }
    }
    for(int i=1;i<=q;i++)   Q[i]=pli(readll(),i);
    sort(Q+1,Q+q+1);
    ll now=0,tim=0;bool d=1;
    for(int _=1;_<=q;_++){
        ll t=Q[_].fi,id=Q[_].se;
        while(true){
            bool D=d;
            if(d){
                if(mp[d].empty()){now+=t-tim;break;}
                ll tp=mp[d].begin()->fi;
                if(now+t-tim<tp){now+=t-tim;break;}
                tim+=tp-now;now=tp;mp[d].begin()->se--;
                if(mp[!d].empty()){now-=t-tim;d^=1;break;}

                ll tb=-mp[!d].begin()->fi,dis=tp-tb;
                int &to_sum=mp[d].begin()->se,&bck_sum=mp[!d].begin()->se;
                // 还未破坏任何一边就结束了
                if((t-tim)/(dis+dis)<min(to_sum,bck_sum)){
                    ll k=(t-tim)/(dis+dis);
                    to_sum-=k;bck_sum-=k;tim+=k*(dis+dis);
                    if(t-tim>=dis&&bck_sum)  bck_sum--,now=tb+t-tim-dis;
                    else    now=tp-(t-tim),d^=1;
                    if(!to_sum)     era(D);
                    if(!bck_sum)    era(!D);
                    break;
                }
                // 破坏了 tb
                if(to_sum>=bck_sum){
                    tim+=bck_sum*(dis+dis);
                    to_sum-=bck_sum;bck_sum=0;d^=1;era(!D);if(!to_sum)era(D);
                }
                else{  // 破坏了 tp
                    tim+=to_sum*(dis+dis);
                    bck_sum-=to_sum;to_sum=0;d^=1;era(D);
                }
            }
            else{
                if(mp[d].empty()){now-=t-tim;break;}
                ll tp=-mp[d].begin()->fi;
                if(now-(t-tim)>tp){now-=t-tim;break;}
                tim+=now-tp;now=tp;mp[d].begin()->se--;
                if(mp[!d].empty()){now+=t-tim;d^=1;break;}

                ll tb=mp[!d].begin()->fi,dis=tb-tp;
                int &to_sum=mp[d].begin()->se,&bck_sum=mp[!d].begin()->se;
                // 还未破坏任何一边就结束了
                if((t-tim)/(dis+dis)<min(to_sum,bck_sum)){
                    ll k=(t-tim)/(dis+dis);
                    to_sum-=k;bck_sum-=k;tim+=k*(dis+dis);
                    if(t-tim>=dis&&bck_sum)  bck_sum--,now=tb-(t-tim-dis);
                    else    now=tp+(t-tim),d^=1;
                    if(!to_sum)     era(D);
                    if(!bck_sum)    era(!D);
                    break;
                }
                // 破坏了 tb
                if(to_sum>=bck_sum){
                    tim+=bck_sum*(dis+dis);
                    to_sum-=bck_sum;bck_sum=0;d^=1;era(!D);if(!to_sum)era(D);
                }
                else{  // 破坏了 tp
                    tim+=to_sum*(dis+dis);
                    bck_sum-=to_sum;to_sum=0;d^=1;era(D);
                }
            }
        }
        tim=t;ans[id]=now;
    }
    for(int i=1;i<=q;i++)   printf("%lld\n",ans[i]);
}