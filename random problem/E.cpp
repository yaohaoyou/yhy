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
const int maxn=2e5+10;
int n,m;
int a[maxn];
void matt(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);a[i]%=m;}
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        // x=[0,a[i]]
        /*
        2 3 5 7 8 11 12 14 15
        m=20
        1 3 4 6 7 10 9 7 6
        */
    }   
    int ans=1e9;
    for(int x=0;x<m;x++){
        int res=0;
        for(int i=1;i<=n;i++){
            res+=min(abs(a[i]-x),m-abs(a[i]-x));
            if(res>=ans) break; 
        }
        ans=min(ans,res);
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}