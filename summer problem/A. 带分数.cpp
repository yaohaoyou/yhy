#pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int B=2.5e6,rB=5e11/B,maxn=B+10,maxk=5e5+10;
ll ans[maxk];
ll L,R;
ll d[maxn];
vector<int> p;
struct number{
    vector<pli> v;
    void init(ll x){
        for(ll i:p){
            if(i*i>x)   break;
            int c=0;
            while(x%i==0)x/=i,c++;
            if(c)   v.eb(i,c);
        }
        if(x^1) v.eb(x,1);
    }
    inline ll operator/(ll y)const{
        ll ret=1;
        for(pii i:v){
            int now=i.se;
            while(y%i.fi==0)y/=i.fi,now--;
            ret*=(now+1);
        }
        return ret;
    }
    inline ll get(){ll ret=1;for(pii i:v)while(i.se--)ret*=i.fi;return ret;}
    inline void print(){for(pli i:v)printf("%d^%d\n",i.fi,i.se);puts("");}
}a[maxk+rB+10];
bool ntpri[maxn];
ll pos;
void seive(){
    for(int i=2;i<=B;i++){
        if(!ntpri[i])   p.eb(i);
        for(int j:p){
            if(1ll*i*j>B)   break;
            ntpri[i*j]=true;
            if(i%j==0)  break;
        }
    }
    fill(d+1,d+B+1,1);
    for(int i:p){
        for(ll j=i,c=2;j<=B;j*=i,c++)
            for(int k=1;j*k<=B;k++)
                if(k%i) d[j*k]*=c;
    }
    pos=L-R/B;
    ll l=L-R/B,r=R-1;
    for(int i:p)
        for(ll j=i,c=1;j<=r;j*=i,c++)
            for(ll k=(l+j-1)/j;j*k<=r;k++)
                if(k%i) a[j*k-pos+1].v.eb(i,c);
    for(ll i=L-R/B;i<R;i++){
        ll x=i/a[i-pos+1].get();
        if(x^1) a[i-pos+1].v.eb(x,1);
    }
}
int main(){
    scanf("%lld%lld",&L,&R);
    pos=L-R/B;
    seive();
    for(int i=2;i<=B;i++)
        for(ll j=(L+i-1)/i*i;j<=R;j+=i) ans[j-L]+=d[i-1];
    for(int i=R/B;i;i--)
        for(ll j=(max(1ll*i*B,L)+i-1)/i*i;j<=R;j+=i)if(j/i>B)ans[j-L]+=a[j-i-pos+1]/i;
    ll out=0;
    for(ll i=L;i<=R;i++){
        ll res=ans[i-L]+1;
        out+=(res^i);
    }
    printf("%lld\n",out);
}