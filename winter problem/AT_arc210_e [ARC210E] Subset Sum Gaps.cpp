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
const int maxn=5010,mod=998244353;
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
int n;
ll a[maxn];
struct node{
    ll l,r;int val;
    bool operator<(const node y)const{return pll(l,r)<pll(y.l,y.r);}
};
vector<node> v;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    v.eb((node){0,0,1});
    for(int i=1;i<=n;i++){
        vector<node> tmp=v;
        int siz=v.size();
        for(node j:tmp) v.eb((node){j.l+a[i],j.r+a[i],j.val});
        inplace_merge(v.begin(),v.begin()+siz,v.end());
        vector<node>().swap(tmp);
        for(int i=0;i<v.size();i++){
            auto [L,R,len]=v[i];
            int j=i+1;
            while(j<v.size()&&101*R>v[j].l*100)    R=max(R,v[j].r),madd(len,v[j].val),j++;
            tmp.eb((node){L,R,len});
            i=j-1;
        }
        v.swap(tmp);
    }
    printf("%d\n",v.size()-1);
    int now=0;
    for(int i=0;i+1<v.size();i++){
        madd(now,v[i].val);
        printf("%lld %lld %d\n",v[i].r,v[i+1].l,now);
    }
}