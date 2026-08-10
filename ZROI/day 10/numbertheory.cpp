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
int n,m;
int a[maxn];
int main(){
    freopen("numbertheory.in","r",stdin);freopen("numbertheory.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    if(n==1)    return puts((a[1]&1)?"B":"A"),0;
    if((n&1)==m)    return puts("A"),0;
    else{
        int x=(n-1)/2,y=n-1-x;
        if(!m)  x=n/2;else x=(n-1)/2;
        y=n-1-x-1;
        int c[2]={0,0};
        for(int i=1;i<=n;i++)   c[a[i]&1]++;
        if(c[0]-y>c[1]-x)   return puts("A"),0;
        for(int i=1;i<n;i++)
            if(!(a[i]&1)&&!(a[i+1]&1))  return puts("A"),0;
        puts("B");
    }
}