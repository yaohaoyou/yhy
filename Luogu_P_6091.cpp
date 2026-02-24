#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e6+10,V=1e6;
int n;
int phi[maxn];
bool ispri[maxn],havrt[maxn];
vector<int> fac;
vector<int> pri;
void PreProcess(){
    mems(ispri,1);
    phi[1]=1;
    for(int i=2;i<=V;i++){
        if(ispri[i]){phi[i]=i-1;pri.eb(i);}
        for(int j:pri){
            if(i*j>V)   break;
            ispri[i*j]=false;
            if(i%j==0){phi[i*j]=phi[i]*j;break;}
            phi[i*j]=phi[i]*phi[j];
        }
    }
    havrt[2]=havrt[4]=true;
    for(int i:pri){
        if(!(i&1))  continue;
        for(ll j=i;j<=V;j*=i){
            havrt[j]=true;
            if(j*2<=V) havrt[j<<1]=true;
        }
    }
}
int qpow(int x,int y,int mod){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
void MakeFactors(int x){
    fac.clear();
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            fac.eb(i);
            while(x%i==0)x/=i;
        }
    }
    if(x^1)fac.eb(x);
}
int FindMinRoot(){
    for(int g=1;true;g++){
        if(qpow(g,phi[n],n)^1)  continue;
        bool flag=true;
        for(int i:fac)
            if(qpow(g,phi[n]/i,n)==1){flag=false;break;}
        if(flag)    return g;
    }
}
vector<int> ans;
void solve(){
    int c,d;ans.clear();
    scanf("%d%d",&n,&d);
    if(!havrt[n])   return puts("0\n"),void();
    c=phi[phi[n]];
    printf("%d\n",c);
    MakeFactors(phi[n]);
    int k=c/d,rt=FindMinRoot();
    ans.eb(rt);
    int g=rt,s=1;
    for(int s=2;s<=phi[n];s++){
        g=1ll*g*rt%n;
        if(__gcd(s,phi[n])==1)  ans.eb(g);
    }
    sort(ans.begin(),ans.end());
    for(int i=d-1;k--&&i<ans.size();i+=d)    printf("%d ",ans[i]);
    puts("");
}
int main(){
    PreProcess();
    int T;
    scanf("%d",&T);
    while(T--)  solve();
}