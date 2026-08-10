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
int n,k;
int a[maxn];
bool bk[maxn];
multiset<int> s;
inline bool check(int x){
    int K=k;
    if(k<=20){
        for(int i=1;i<=n;i++)   bk[i]=0;
        int ctt=0;
        while(K--){
            int now=x;
            for(int i=n;i;i--){
                if(bk[i]||a[i]>now)   continue;
                bk[i]=true;now-=a[i];ctt++;
            }
            if(ctt==n)  return true;
        }
        return false;
    }
    s.clear();
    for(int i=1;i<=n;i++)   s.ep(a[i]);
    while(K--){
        int now=x;
        while(true){
            auto it=s.upper_bound(now);
            if(it==s.begin())   break;
            it--;now-=*it;
            s.erase(it);
        }
        if(s.empty())   return true;
    }
    return false;
}
void matt(){
    scanf("%d%d",&n,&k);
    int sum=0,mx=0;
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);sum+=a[i];mx=max(mx,a[i]);}
    sort(a+1,a+n+1);
    for(int i=max(mx,(sum+k-1)/k);1;i++)
        if(check(i)){printf("%d\n",i);break;}
}
int main(){int T;scanf("%d",&T);while(T--)matt();}
/*
[sum v/k,1000*n/k]
n/k 1000*n/k
n=1000,k=1
1000 1000000

(1000n-sumv)*k
k>20 -> 1000*n/20 = 50000
k<20 -> 1000*n*20 = 
*/