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
const int maxn=8e6+10,mod=1e9+7;
int n;
int a[maxn],fac[maxn],inv[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
    inline int I(int x){return qpow(x,mod-2);}
}
using namespace FastMod;
int ipq[maxn];
int st[maxn];
int S[maxn];
vector<int> ls;
bool era[maxn];
void seive(){
    const int N=8e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    ipq[0]=1;for(int i=1;i<=N;i++)ipq[i]=immul(ipq[i-1],(mod+1)>>1);
}
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    // freopen("skydive.in","r",stdin);freopen("skydive.out","w",stdout);
    seive();
    scanf("%d",&n);
    int ans=0,mx=0;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),mx=max(mx,a[i]);
    for(int i=1;i<=n;i++){
        for(int j=0;j<=a[i];j++)
        madd(ans,1ull*min(j,a[i]-j)*C(a[i],j)%mod*ipq[a[i]]%mod);
    }
    for(int i=1;i<=n;i++){
        st[i]=st[i-1]+a[i-1]+1;
        for(int j=a[i];~j;j--)    S[st[i]+j]=imadd(S[st[i]+j+1],C(a[i],j));
    }
    for(int i=1;i<=n;i++)   ls.eb(i);
    for(int k=1;k<=mx;k++){
        int res=1;
        for(int i:ls){
            if((a[i]+k+k+1)/2>a[i]){era[i]=true;continue;}
            int s=immul(S[st[i]+(a[i]+k+k+1)/2],2);
            if((a[i]+k+k+1)&1)  mdel(s,C(a[i],(a[i]+k+k+1)/2));
            // for(int o=k;o<=a[i];o++)    madd(s,C(a[i],(a[i]+o+k+1)/2));
            mmul(s,ipq[a[i]]);
            mmul(res,imdel(1,s));
        }
        mdel(ans,imdel(1,res));
        vector<int> nw;nw.clear();
        for(int i:ls)if(!era[i])nw.eb(i);
        ls.swap(nw);
    }
    printf("%d\n",ans);
}