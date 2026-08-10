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
const int maxn=1e6+10;
int n;
int a[maxn];
vector<int> v;
void makefactors(int x){
    for(int i=2;1ll*i*i<=x;i++){
        if(x%i==0){
            v.eb(i);
            while(x%i==0)x/=i;
        }
    }
    if(x^1) v.eb(x);
}
int main(){
    scanf("%d",&n);
    makefactors(n);
    mems(a,0x3f);
    for(int i=2;i<=n;i++){
        if(a[i]!=a[0])    continue;
        for(int j=i;j<=n;j+=i)  a[j]=min(a[j],max(i+1,j-i+1));
    }
    int ans=1e9;
    for(int i:v){
        // n-i+1,n
        for(int j=n-i+1;j<=n;j++)   ans=min(ans,a[j]);
    }
    printf("%d\n",ans);
}