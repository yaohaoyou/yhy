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
char c[maxn];ll a[maxn];
int main(){
    cin>>n;
    ll s=0;
    for(int i=1;i<=n;i++){
        cin>>c[i]>>a[i];
        s+=a[i];
        if(s>100)   exit(puts("Too Long")&0);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=a[i];j++)    putchar(c[i]);
    }
}