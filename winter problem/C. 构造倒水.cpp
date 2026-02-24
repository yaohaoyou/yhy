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
const int maxn=1e4+10;
int n,m;
int a[maxn],b[maxn];
inline vector<pii> sol1(){
    vector<pii> ans;
    for(int i=1;i<n;i++)if(a[i])ans.eb(i,n);
    for(int i=n;i>1;i--)ans.eb(i,i-1);
    queue<int> q0;
    for(int i=1;i<=n;i++)if(!b[i])q0.ep(i);
    for(int i=1;i<=n;i++){
        if(b[i]>1){
            int x=b[i]-1;
            while(x--)  ans.eb(q0.front(),i),q0.pop();
        }
    }
    return ans;
}
inline vector<pii> sol2(){
    vector<pii> ans;
    queue<int> q0;
    for(int i=1;i<=n;i++)if(!a[i])q0.ep(i);
    if(!q0.empty()){
        if(a[1])    ans.eb(1,q0.front()),q0.pop(),q0.ep(1);
        else    q0.pop(),q0.ep(1);
        for(int i=2;i<=n;i++)if(a[i]>1){
            int x=a[i]-1;
            while(x--){if(i^1)ans.eb(i,1);if(q0.front()^1)ans.eb(1,q0.front());q0.pop();}
        }
    }
    while(!q0.empty())q0.pop();
    for(int i=1;i<=n;i++)if(!b[i])q0.ep(i);
    for(int i=1;i<=n;i++){
        if(b[i]>1){
            int x=b[i]-1;
            while(x--)  ans.eb(q0.front(),i),q0.pop();
        }
    }
    return ans;
}
inline vector<pii> sol3(){
    vector<pii> ans;
    for(int i=1;i<n;i++)if(a[i])ans.eb(i,n);
    for(int i=n-1;i;i--){
        if(b[i]){
            ans.eb(n,b[i]);
            if(b[i]^i)  ans.eb(b[i],i);
        }
    }
    return ans;
}
void matt(int _cases){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    bool flag=true;
    for(int i=1;i<=n;i++)if(a[i]!=b[i]){flag=false;break;}
    if(flag)    return puts("0"),void();
    vector<pii> v1=sol1(),v2=sol2(),v3=sol3();
    if(v1.size()>v2.size()) v1.swap(v2);
    if(v1.size()>v3.size()) v1.swap(v3);
    printf("%d\n",v1.size());
    for(auto [i,j]:v1){
        printf("%d %d\n",i,j);
        int d=min(a[i],j-a[j]);
        a[i]-=d;a[j]+=d;
    }
    // puts("");
    // for(int i=1;i<=n;i++)   printf("%d %d\n",a[i],b[i]);
    for(int i=1;i<=n;i++)   assert(a[i]==b[i]);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}