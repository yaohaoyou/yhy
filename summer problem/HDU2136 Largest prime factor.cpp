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
vector<int> p;
void makefactors(){
    const int N=maxn-10;
    for(int i=2;i<=N;i++){
        if(!a[i])   p.eb(i),a[i]=p.size();
        for(int j:p){
            if(1ll*i*j>N)   break;
            a[i*j]=max(a[i],a[j]);
            if(i%j==0)  break;
        }
    }
}
int main(){
    makefactors();
    while(~scanf("%d",&n))  printf("%d\n",a[n]);
}