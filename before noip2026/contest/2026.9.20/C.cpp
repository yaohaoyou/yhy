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
mt19937_64 rd(time(0));
const int maxn=2e6+10,mod=998244353;
inline int Matt(){return abs((int)rd()%mod);}
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
const int bs=Matt(),bs2=Matt();
bool mem1;
int n,m;
int msk['z'+1];
string s[maxn],ans;
struct H{
    int h,h2;
    H(int x=0,int y=0){h=x;h2=y;}
    inline bool operator==(const H &x){return h==x.h&&h2==x.h2;}
    inline H operator+(const char &x){return H(imadd(immul(h,bs),msk[x]),imadd(immul(h2,bs2),msk[x]));}
    inline H operator+(const H &x){return H(imadd(h,x.h),imadd(h2,x.h2));}
    inline H operator-(const H &x){return H(imdel(h,x.h),imdel(h2,x.h2));}
    inline H operator*(const H &x){return H(immul(h,x.h),immul(h2,x.h2));}
    inline H operator/(const H &x){return H(immul(h,qpow(x.h,mod-2)),immul(h2,qpow(x.h2,mod-2)));}
};
H pre[maxn],suf[maxn],pq[maxn],inv[maxn];
inline H cs(int l,int r){return l?pre[r]-pre[l-1]*pq[r-l+1]:pre[r];}
inline H ca(int l,int r){
    l=ans.length()+1-l;r=ans.length()+1-r;
    swap(l,r);
    // H res;for(int i=r-1;i>=l-1;i--)res=res+ans[i];return res;
    return (suf[r]-suf[l-1])*inv[l-1];
}
inline int rev(int x){return ans.length()-x-1;}
bool mem2;
void matt(int _cases){
    ans="";
    cin>>n;m=0;
    for(int i=1;i<=n;i++)   cin>>s[i],m+=s[i].length();
    pq[0]=H(1,1);for(int i=1;i<=m;i++)pq[i]=pq[i-1]*H(bs,bs2);
    inv[0]=H(1,1);inv[1]=H(qpow(bs,mod-2),qpow(bs2,mod-2));for(int i=2;i<=m;i++)inv[i]=inv[i-1]*inv[1];
    for(int i=n;i;i--){
        // string suf="",res=s[i].back()+ans;
        // for(int j=s[i].length()-1;~j;j--){
        //     suf=s[i][j]+suf;
        //     res=min(res,suf+ans);
        // }
        pre[0]=H(msk[s[i][0]],msk[s[i][0]]);for(int j=1;j<s[i].length();j++)pre[j]=pre[j-1]+s[i][j];
        int L=s[i].length();
        auto calc=[&](int l,int r){
            if(r<L) return cs(l,r);
            return cs(l,L-1)*pq[r-L+1]+ca(1,r-L+1);
        };
        int mn=L-1;
        // printf("i = %d\n",i);
        for(int j=L-2;~j;j--){
            int l=1,r=L+ans.size()-mn,p=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(calc(j,j+mid-1)==calc(mn,mn+mid-1))  p=mid,l=mid+1;
                else r=mid-1;
            }
            // printf("%d %d : %d %d %d\n",j,mn,p,calc(j,j+3-1),calc(mn,mn+3-1));
            if(p==L+ans.size()-mn)  continue;
            char x,y;
            if(j+p<L)   x=s[i][j+p];
            else x=ans[rev(j+p-L)];
            if(mn+p<L)  y=s[i][mn+p];
            else y=ans[rev(mn+p-L)];
            // assert(x^y);
            if(x<y) mn=j;
        }
        for(int j=L-1;j>=mn;j--){
            ans+=s[i][j];
            int x=ans.length();
            suf[x]=suf[x-1]+pq[x-1]*H(msk[s[i][j]],msk[s[i][j]]);
        }
    }
    reverse(ans.begin(),ans.end());
    cout<<ans<<'\n';
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    for(int i='a';i<='z';i++)msk[i]=Matt();
    int T;cin>>T;for(int i=1;i<=T;i++)matt(i);
}