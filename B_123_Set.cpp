#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e9+2;
int n;
int ans;
bitset<maxn> bs,mus;
int main(){
    scanf("%d",&n);
    int l=n/3,r=l/2;
    for(int i=l;i>r;i--){bs.set(i);bs.set(i*2);bs.set(i*3);ans++;}
    for(int i=r;i;i--){
        if(i%2&&i%3){bs.set(i);bs.set(i*2);bs.set(i*3);ans++;continue;}
        if(mus[i]||!bs[i*3])
        if(!(i%3))  mus.set(i/3);
        else if(!(i&1)) mus.set(i/2);
    }
    for(int i=l+1;i<=n;i++){
        if(!bs[i]){if(1ll*i*2<=n)bs.set(i*2);ans++;}
    }
    printf("%d\n",ans);
}