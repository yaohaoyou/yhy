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
const int maxn=2e5+10;
int n;
int a[maxn];
ll s[maxn];
stack<pli> stk;
inline int avg(pli x,bool flag=false){
    if(flag)    return (x.fi+x.se-1)/x.se;
    return x.fi/x.se;
}
void matt(int _cases){
    stack<pli>().swap(stk);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i]-=i;a[i]+=1e9;s[i]=s[i-1]+a[i];
    }
    for(int i=1;i<=n;i++){
        pli now=pli(a[i],1);
        while(!stk.empty()&&avg(stk.top(),1)>avg(now))  now.fi+=stk.top().fi,now.se+=stk.top().se,stk.pop();
        stk.ep(now);
    }
    int p=n;
    while(!stk.empty()){
        pli x=stk.top();stk.pop();
        p=p-x.se+1;
        for(int i=p;i<=p+x.se-1;i++)    a[i]=avg(x);
        int lst=x.fi%x.se;
        for(int i=p+x.se-lst;i<=p+x.se-1;i++)   a[i]++;
        p--;
    }
    ll sum=0,ans=0;
    for(int i=1;i<=n;i++){sum+=a[i];ans+=s[i]-sum;}
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
// 3 3 1
// 2 2 3
// 3 6 7
// 2 4 7