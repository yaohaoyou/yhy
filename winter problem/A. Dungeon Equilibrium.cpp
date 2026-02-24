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
const int maxn=110;
int n;
int a[maxn],s[maxn];
void matt(int _cases){
    mems(s,0);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),s[a[i]]++;
    int ans=0;
    for(int i=0;i<=n;i++){
        if(s[i]>=i)  ans+=s[i]-i;
        else ans+=s[i];
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}