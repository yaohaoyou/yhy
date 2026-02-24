#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e6+10,R=1e6;
int n;
int phi[maxn];bool ispri[maxn];
ll ans[maxn];
vector<int> pri;
void initmu(){
    mems(ispri,1);
    phi[1]=1;
    for(int i=2;i<=R;i++){
        if(ispri[i]){pri.eb(i);phi[i]=i-1;}
        for(int j:pri){
            if(i*j>R)  break;
            ispri[i*j]=false;
            if(i%j==0){phi[i*j]=phi[i]*j;break;}
            else    phi[i*j]=phi[i]*phi[j];
        }
    }
    for(int i=1;i<=R;i++){
        for(int j=i;j<=R;j+=i){
            ans[j]+=(1ll*i*phi[i]);
        }
    }
}
void solve(){
    scanf("%d",&n);
    printf("%lld\n",1ll*n*(ans[n]+1)/2);
}
int main(){initmu();int t;scanf("%d",&t);while(t--)solve();}