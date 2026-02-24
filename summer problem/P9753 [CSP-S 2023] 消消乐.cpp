#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
mt19937_64 matt(time(0));
const int maxn=2e6+10;
const ull base=matt();
int n;
unordered_map<ull,int> mp;
ull hsh[maxn];
char a[maxn];
stack<char> stk;
int main(){
    scanf("%d%s",&n,a+1);
    mp[0]++;
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(!stk.empty()&&stk.top()==a[i])   stk.pop();
        else stk.ep(a[i]),hsh[stk.size()]=hsh[stk.size()-1]*base+a[i];
        ans+=(mp[hsh[stk.size()]]++);
    }
    printf("%lld\n",ans);
}