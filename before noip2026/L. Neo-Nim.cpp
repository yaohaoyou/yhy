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
const int maxn=1e5+10;
bool mem1;
int n,k;
int a[maxn];
unordered_map<int,int> mp;
inline int id(int x){if(x%k==1)return 1;if(x%k==2%k)return 2;return 0;}
bool mem2;
void matt(int _cases){
    mp.clear();
    scanf("%d%d",&n,&k);
    int mx=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        mp[a[i]]++;gmx(mx,a[i]);
    }
    if(mp[1]+mp[2]/2>=1)    return puts("Bob"),void();
    if(k==2){
        mp.clear();
        for(int i=1;i<=n;i++)mp[a[i]%3]++;
        if(mp[1]||mp[2]>=2||mp[0]==n)   puts("Bob");
        else    puts("Ana");
    }
    else if(k==3){
        if(!mp[2]){
            if(mx>=6||mp[3]||(mp[5]&1)) puts("Ana");
            else    puts("Bob");
        }
        else{
            if(mx>=7||mp[6]>1||!(mp[5]&1)) puts("Ana");
            else    puts("Bob");
        }
        return;
    }
    else puts("Ana");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}