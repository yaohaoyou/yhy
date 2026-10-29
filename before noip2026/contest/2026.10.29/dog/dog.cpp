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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e6+10;
bool mem1;
int n;
int a[maxn];
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    if(!*min_element(a+1,a+n+1))    return puts("No"),void();
    for(int i=n;i;i--)  a[i]-=a[i-1];
    ll s=0;
    for(int i=1;i<=n;i++){
        if(a[i]>0)  s+=a[i]-1;
        else if(a[i]+s<0)   return puts("No"),void();
        else    s+=a[i];
    }
    puts("Yes");
}
int main(){freopen("dog.in","r",stdin);freopen("dog.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}