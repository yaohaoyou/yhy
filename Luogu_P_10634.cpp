#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e6+10,mod=1e9+7;
int n,m;
int len=-1;
int a[maxn],b[maxn];

int bs1;
int pq1[maxn],inv1;
int hsh1[30],tar1[30];

int bs2;
int pq2[maxn],inv2;
int hsh2[30],tar2[30];

int s[maxn],t[maxn],tmp[maxn];
vector<int> ans;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
inline void check(int x){
    int l=-1;
    for(int i=0;i<26;i++){
        if(!hsh1[i]) continue;
        l++;
        if((hsh1[i]^tar1[l])||(hsh2[i]^tar2[l]))   return;
    }
    if(l^len)   return;
    ans.eb(x+1);
}
int main(){
    // freopen("youran.in","r",stdin);freopen("youran.out","w",stdout);
    srand(time(0));
    scanf("%d%d%d",&n,&m,&bs1);
    bs1=rand()%17+1;bs2=rand()%37+1;
    for(int i=1;i<=n;i++)   scanf("%d",&s[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&t[i]);
    inv1=qpow(bs1,mod-2);inv2=qpow(bs2,mod-2);
    pq1[0]=1;pq2[0]=1;
    for(int i=1;i<=m;i++)   pq1[i]=immul(pq1[i-1],bs1),pq2[i]=immul(pq2[i-1],bs2);
    for(int i=1;i<=m;i++){
        madd(hsh1[s[i]],pq1[i]);
        madd(tar1[t[i]],pq1[i]);
        madd(hsh2[s[i]],pq2[i]);
        madd(tar2[t[i]],pq2[i]);
    }
    for(int i=0;i<26;i++)
        if(tar1[i])  tar1[++len]=tar1[i],tar2[len]=tar2[i];
    check(0);
    for(int i=1;i+m<=n;i++){
        mdel(hsh1[s[i]],bs1);
        mdel(hsh2[s[i]],bs2);
        for(int j=0;j<26;j++)   mmul(hsh1[j],inv1),mmul(hsh2[j],inv2);
        madd(hsh1[s[i+m]],pq1[m]);
        madd(hsh2[s[i+m]],pq2[m]);
        check(i);
    }
    printf("%d\n",(int)ans.size());
    for(int i:ans)   printf("%d\n",i);
}