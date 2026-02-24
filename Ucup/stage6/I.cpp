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
const int maxn=5010;
int n;
map<int,int> mp[maxn];
int sum[maxn];
int main(){
    scanf("%d",&n);
    while(n--){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        if(mp[x].count(y)){puts("0");continue;}
        if(z<240){
            printf("%d\n",y);
            mp[x][y]=1;
            sum[x]++;
        }
        else{
            if(sum[x]<3)    printf("%d\n",y),mp[x][y]=1,sum[x]++;
            else mp[x][y]=1,puts("0");
        }
    }
}