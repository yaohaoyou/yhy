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
const int maxn=2e6+10;
bool mem1;
vector<int> solve(int n){
    if(n==1)  return vector<int>{0};
    int m=(n+1)>>1;
    vector<int> v=solve(m),ret;
    bool o=0;
    if((n&1)&&find(v.begin(),v.end(),m-1)-v.begin()&1) o=1;
    for(int i:v){
        if((n&1)&&i==m-1)   ret.eb(n-1);
        else{
            ret.eb(i<<1|o);
            o^=1;
            ret.eb(i<<1|o);
        }
    }
    return ret;
}
bool mem2;
void matt(int _cases){
    int n;
    scanf("%d",&n);
    vector<int> v=solve(n);
    for(int i:v)    printf("%d ",i);puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}