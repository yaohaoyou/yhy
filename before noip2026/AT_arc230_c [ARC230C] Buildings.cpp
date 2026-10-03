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
const int maxn=4e5+10,mod=998244353;
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
int n,ans,fac=1;
int a[maxn],buc[maxn];
int siz[maxn];
int solve(){
    int m=n,res=fac;
    stack<int> stk;
    for(int i=0;i<=n;i++){
        int u=i;
        while(!stk.empty()&&a[stk.top()]==a[u]){
            a[++m]=a[stk.top()]-1;
            if(a[m]<0)  return 0;
            siz[m]=siz[stk.top()]+siz[u]+1;
            mmul(res,qpow(siz[m],mod-2));
            u=m;
            stk.pop();
        }
        stk.ep(u);
    }
    return (stk.size()==1&&!a[m])*res;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)mmul(fac,i);
    for(int i=1;i<n;i++)   scanf("%d",&a[i]),buc[a[i]]++;
    vector<int> v;
    for(int i=n,tag=0;i;i--){
        if((buc[i]+tag)&1)  v.eb(i);
        tag=(buc[i]+tag+1)>>1;
    }
    if(v.empty()||v.size()>=3) return puts("0"),0;
    if(v.size()==1){
        a[0]=a[n]=v[0]+1;
        printf("%d\n",solve());
    }
    else if(v.size()==2){
        a[0]=v[0];a[n]=v[1];
        ans=solve();
        a[0]=v[1];a[n]=v[0];
        madd(ans,solve());
        printf("%d\n",ans);
    }
}