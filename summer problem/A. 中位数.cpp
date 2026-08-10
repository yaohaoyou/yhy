#include<bits/stdc++.h>
// #include "median.h"
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
int n,k;
int a[maxn],b[maxn];
int buc[maxn];
void init(int c, int t){return;}
bool check(int x){
    mems(buc,0);
    for(int i=1;i<=n;i++)   b[i]=a[i]>=x;
    b[n+1]=0;
    int c=0;
    vector<pii> v;v.clear();
    for(int i=1;i<=n;i++){
        if(b[i]){
            c++;
            if(i<n&&!b[i+1])    i++,v.eb(1,2);
            else v.eb(1,1);
        }
        else{
            if(b[i+1])  c++,i++,v.eb(1,-2);
            else{
                int j=i;while(j<=n&&!b[j])j++;v.eb(0,j-i);
                i=j-1;
            }
        }
    }
    int lst=-1,d=v.size();
    if(d<=k)    return c>=(k+1)/2;
    // if(x==62){
    //     printf("%d %d\n",c,d);
    //     for(pii i:v)printf("%d,%d ",i.fi,i.se);puts("");
    // }
    for(int i=0;i<v.size();i++){
        if(!v[i].fi){
            if(~lst)    buc[i-lst]++;
            lst=i;
        }
    }
    for(int i=1;i<=n;i++){
        while(buc[i]--){
            if(d-i<k){c-=d-k;d=k;break;}
            d-=i;c-=i-1;
            if(d==k)    break;
        }
        buc[i]=0;
        if(d<=k){c+=k-d;break;}
    }
    // if(d>k) c-=(d-k);
    return c>=(k+1)/2;
}
int median(int N,int K,vector<int> A){
    n=N;k=K;
    for(int i=1;i<=n;i++)   a[i]=A[i-1];
    int l=1,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,l=mid+1;
        else    r=mid-1;
    }
    return ans;
}

signed main() {
    int c, t;
    std::cin >> c >> t;
    init(c, t);
    for (int _ = 0; _ < t; _++) {
        int n, k;
        std::cin >> n >> k;
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) std::cin >> a[i];
        std::cout << median(n, k, a) << '\n';
    }
    return 0;
}
