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
const int maxn=10;
int n;
int a[maxn][10],p[4];
int main(){
    n=3;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=6;j++)   cin>>a[i][j];
    iota(p+1,p+n+1,1);
    double ans=0;
    do{
        double res=1;
        for(int i=1;i<=n;i++){
            int c=count(a[i]+1,a[i]+6+1,p[i]+3);
            res*=1.0*c/6;
        }
        ans+=res;
    }while(next_permutation(p+1,p+n+1));
    printf("%.10lf",ans);
}