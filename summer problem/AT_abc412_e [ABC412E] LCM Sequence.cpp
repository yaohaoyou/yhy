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
const int maxV=1.1e7;
ll l,r;int V;
vector<int> p;
int ans=1;
bool ntpri[maxV],np[maxV];
void makeprimes(){
    for(int i=2;i<=V;i++){
        if(!ntpri[i])   p.eb(i);
        for(int j:p){
            if(1ll*i*j>V)   break;
            ntpri[i*j]=true;
            if(i%j==0)  break;
        }
    }
}
int main(){
    scanf("%lld%lld",&l,&r);l++;
    V=sqrt(r)+10;makeprimes();
    for(int i:p){
        for(ll j=max(2ll,1ll*(l+i-1)/i)*i;j<=r;j+=i){
            np[j-l]=true;
            ll t=j;
            while(t%i==0)t/=i;
            ans+=(t==1);
        }
    }
    ans+=count(np,np+r-l+1,false);
    printf("%d\n",ans);
}