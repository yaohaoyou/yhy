#include<bits/stdc++.h>
#include "pen.h"
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
const int maxn=20;
int n=15;
int a[maxn];
int f[maxn];
bool p[maxn];
// int main(){
//     iota(a+2,a+n+1,1);
//     shuffle(a+1,a+n+1,g);
//     while(true){
//         int p=rand()%n+1;
//         while(f[p]) p=rand()%n+1;
//         f[p]=true;
//         if(!a[p])   break;
//         a[p]--;
//     }
//     int sum=0,cnt=0;
//     for(int i=1;i<=n;i++)if(!f[i])sum+=a[i],cnt++;
//     printf("%.2f\n",1.0*sum/cnt);
// }
pair<int, int> solve_one(int N){
    mems(f,0);mems(p,1);
    int lst=0;
    for(int i=1;i<=7;i++){
        bool flag=false;
        for(int j=1;j<=n;j++){
            if(!p[j])    continue;
            if(i-f[j]>=5||(i>=6&&i-f[j]>=4)){lst=j;flag=true;break;}
            while(f[j]<i){
                f[j]++;
                p[j]=try_write(j);
            }
            if(!p[j])   break;
        }
        if(flag)    break;
    }
    vector<pii> v;
    for(int i=1;i<=n;i++)if(p[i])v.eb(-f[i],i);
    sort(v.begin(),v.end(),greater<pii>());
    if(v.size()>1)  return pii(v[0].se,v[1].se);
    else    return pii(n-1,n);
    // for(int i=n;i;i--)if(p[i]&&i!=lst){
    //     if(lst) return pii(lst,i);
    //     else lst=i;
    // }
    // return pii(lst,lst%n+1);
}
// int main(){
//     int T=100000,C=63600;
//     printf("%d %d %d\n",T,n,C);
//     while(T--){
//         iota(a+2,a+n+1,1);
//         shuffle(a+1,a+n+1,rd);
//         for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
//     }
// }