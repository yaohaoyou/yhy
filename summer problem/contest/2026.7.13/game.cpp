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
const int maxn=1e5+10;
int n,k;
int a[maxn];
set<int> s[2];
void matt(int _cases){
    s[0].clear();s[1].clear();
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){scanf("%1d",&a[i]);s[a[i]].ep(i);}
    if(s[0].empty()||s[1].empty())  return puts("win"),void();
    if(*prev(s[0].end())-*s[0].begin()+1<=k||*prev(s[1].end())-*s[1].begin()+1<=k)  return puts("win"),void();
    for(int i=1;i+k-1<=n;i++){
        for(int o:{0,1}){
            // [i,i+k-1] := o
            auto it=s[!o].lower_bound(i);
            int pr=it==s[!o].begin()?0:*(--it);
            it=s[!o].upper_bound(i+k-1);
            int nx=it==s[!o].end()?0:*it;
            if(pr&&nx)  return puts("tie"),void();
            if(pr){
                if(pr-*s[!o].begin()+1>k)  return puts("tie"),void();
            }
            else if(nx){
                if(*prev(s[!o].end())-nx+1>k)   return puts("tie"),void();
            }
            else assert(0);
        }
    }
    puts("lose");
}
int main(){freopen("game.in","r",stdin);freopen("game.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}