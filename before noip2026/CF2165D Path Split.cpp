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
const int maxn=2e6+10;
bool mem1;
int n;
int a[maxn];
set<int> l[maxn],r[maxn];
bool mem2;
void matt(int _cases){
    for(int i=0;i<=n+n;i++)l[i].clear(),r[i].clear();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),l[a[i]].ep(i),r[a[i]].ep(i);
    int ans=n;
    for(int i=n+n;i;i--){
        vector<int> tmp;
        for(int j:r[i+1]){
            auto it=l[i].upper_bound(j);
            if(it!=l[i].begin()){
                ans--;
                it--;
                l[i].erase(it);
            }
        }
        for(auto j=r[i-1].begin();j!=r[i-1].end();){
            auto it=l[i].upper_bound(*j);
            if(it!=l[i].begin()){
                ans--;
                it--;
                l[i].erase(it);
                j=r[i-1].erase(j);
            }
            else    j++;
        }
    }
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}