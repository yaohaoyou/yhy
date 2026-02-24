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
const int maxn=1010;
int n,m;
int a[maxn];
void matt(int _cases){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!a[i])   continue;
        bool flag=false;
        for(int j=max(1,i-m+1);j<i;j++){
            if(a[j])flag=true;
        }
        if(!flag)   ans++;
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}