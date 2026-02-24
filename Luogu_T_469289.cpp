#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const ll x1=1e18,V=1e8;
ll x2;
bool notpri[V+10];
vector<int> pri;
void init(){
    for(int i=2;i<=V;i++){
        if(!notpri[i])  pri.eb(i);
        for(int j:pri){
            if(1ll*i*j<=V)  notpri[i*j]=true;
            else    break;
            if(i%j==0)  break;
        }
    }
}
int find(ll x){
    for(int i:pri){
        if(1ll*i*i>x)   break;
        if(x%i==0)  return i;
    }
    return 2;
}
void solve(){
    ll r1,r2;
    cout<<"? "<<x1<<endl;
    // r1=x1%ans;
    cin>>r1;
    x2=x1-r1-1;
    cout<<"? "<<x2<<endl;
    // r2=x2%ans;
    cin>>r2;
    cout<<"! "<<r2+1<<endl;
    // cout<<ans<<"\n\n";
}
int main(){int T;cin>>T;while(T--)solve();}