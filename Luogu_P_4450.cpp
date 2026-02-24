#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e6+10,R=1e6;
int a,b,c,d,k;
int mu[maxn],smu[maxn];bool ispri[maxn];
vector<int> pri;
void initmu(){
    mems(ispri,1);
    mu[1]=1;
    for(int i=2;i<=R;i++){
        if(ispri[i]){pri.eb(i);mu[i]=-1;}
        for(int j:pri){
            if(i*j>R)  break;
            ispri[i*j]=false;
            if(i%j==0)  mu[i*j]=0;
            else mu[i*j]=mu[i]*mu[j];
            if(i%j==0)  break;
        }
    }
    for(int i=1;i<=R;i++) smu[i]=smu[i-1]+mu[i];
}
inline ll calc(int x,int y){
    ll ans=0;
    for(int l=1,r;l<=min(x,y);l=r+1){
        r=min({x/(x/l),y/(y/l),min(x,y)});
        // ans+=mu[i]*(x/i)*(y/i);
        ans+=1ll*(smu[r]-smu[l-1])*(x/l)*(y/l);
    }
    return ans;
}
void solve(){
    scanf("%d%d%d",&b,&d,&k);
    a=1;c=1;
    printf("%lld\n",calc(b/k,d/k)-calc((a-1)/k,d/k)-calc(b/k,(c-1)/k)+calc((a-1)/k,(c-1)/k));
}
int main(){initmu();int t=1;while(t--)solve();}