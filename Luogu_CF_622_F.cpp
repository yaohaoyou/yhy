#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e6+10,mod=1e9+7;
int n,k;
int a[maxn];
bool bk[maxn];
vector<int> fac;
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace MyMod;
void seive(){
    a[1]=1;
    for(int i=2;i<=k+10;i++){
        if(!bk[i]){fac.eb(i);a[i]=qpow(i,k);}
        for(int j:fac){
            if(1ll*i*j>k+10)   break;
            bk[i*j]=true;
            a[i*j]=immul(a[i],a[j]);
            if(i%j==0)  break;
        }
    }
    for(int i=1;i<=k+10;i++) madd(a[i],a[i-1]);
}
int s[maxn],pre[maxn],suf[maxn];
int main(){
    scanf("%d%d",&n,&k);
    seive();
    s[0]=1;
    pre[0]=suf[k+11]=1;
    for(int i=1;i<=k+10;i++){pre[i]=immul(pre[i-1],imdel(n,i));s[i]=immul(s[i-1],i);}
    for(int i=k+10;i;i--)    suf[i]=immul(suf[i+1],imdel(n,i));
    int ans=0;
    for(int i=1;i<=k+10;i++){
        int p=1ll*a[i]*pre[i-1]%mod*suf[i+1]%mod,q=1ll*s[i-1]*s[k+10-i]%mod;
        if((k+10-i)&1)   q=mod-q;
        madd(ans,immul(p,qpow(q,mod-2)));
        // int res=a[i];
        // for(int j=1;j<i;j++)    mmul(res,immul(imdel(n,j),qpow(imdel(i,j),mod-2)));
        // for(int j=i+1;j<=k+10;j++)   mmul(res,immul(imdel(n,j),qpow(imdel(i,j),mod-2)));
        // madd(ans,res);
    }
    printf("%d\n",ans);
}