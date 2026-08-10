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
const int V=2e6,maxv=V+10;
bool ntp[maxv];
ll _phi[maxv];int _mu[maxv];
vector<int> p;
void init(){
    _phi[1]=_mu[1]=1;
    for(int i=2;i<=V;i++){
        if(!ntp[i]) p.eb(i),_phi[i]=i-1,_mu[i]=-1;
        for(int j:p){
            if(1ll*i*j>V)   break;
            ntp[i*j]=true;
            if(i%j==0){
                _phi[i*j]=_phi[i]*j;
                break;
            }
            _phi[i*j]=_phi[i]*_phi[j];
            _mu[i*j]=_mu[i]*_mu[j];
        }
    }
    for(int i=2;i<=V;i++)   _phi[i]+=_phi[i-1],_mu[i]+=_mu[i-1];
}
unordered_map<int,ll> phi;
unordered_map<int,int> mu;
ll sumphi(int x){
    if(x<=V)    return _phi[x];
    if(phi.find(x)!=phi.end())  return phi[x];
    auto sg=[&](int x){return x;};auto sfg=[&](int x){return 1ll*x*((ll)x+1)/2;};
    ll res=sfg(x);
    for(ll l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        res-=(sg(r)-sg(l-1))*sumphi(x/l);
    }
    res/=sg(1);
    return phi[x]=res;
}
int summu(int x){
    if(x<=V)    return _mu[x];
    if(mu.find(x)!=mu.end())  return mu[x];
    auto sg=[&](int x){return x;};auto sfg=[&](int x){return 1;};
    ll res=sfg(x);
    for(ll l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        res-=(sg(r)-sg(l-1))*summu(x/l);
    }
    res/=sg(1);
    return mu[x]=res;
}
int n;
void matt(){
    scanf("%d",&n);
    printf("%lld %d\n",sumphi(n),summu(n));
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}