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
bool mem1;
const int maxn=3e5+10;
int n;
int a[maxn];
ll b[maxn],out[maxn];
stack<int> stk;
bool mem2;
inline ll calc(int x,int i){
    return 1ll*a[x]*a[x]-1ll*(i+a[i]-x)*(i+a[i]-x);
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int mx=1;ll ans=0;
    for(int i=n;i;i--){
        stk.ep(i);
        while(!stk.empty()&&stk.top()+a[stk.top()]<=i+a[i]){
            ans-=b[stk.top()];
            stk.pop();
        }
        if(!stk.empty()){
            ans-=b[stk.top()];
            b[stk.top()]=calc(stk.top(),i);
            ans+=b[stk.top()];
        }
        stk.ep(i);
        b[i]=1ll*a[i]*a[i];
        ans+=b[i];
        out[i]=ans;
    }
    for(int i=1;i<=n;i++)   printf("%lld\n",out[i]);
    // for(int i=1;i<=n;i++){
    //     if(mx<i+a[i]){
    //         ans+=1ll*a[i]*a[i]-1ll*(mx-i)*(mx-i);
    //         mx=i+a[i];
    //     }
    // }
}