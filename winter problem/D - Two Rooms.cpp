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
const int maxn=55;
int n;
int a[maxn][maxn],ss[maxn];
unordered_set<int> s[2];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]),ss[i]+=a[i][j];
    for(int i=1;i<=n;i++)s[0].ep(i);
    while(true){
        bool flag=true;
        for(int i:s[0]){
            int sum=0;
            for(int j:s[0])sum+=a[i][j];
            if(sum<ss[i]-sum){s[0].erase(i);s[1].ep(i);flag=false;break;}
        }
        if(!flag)continue;
        for(int i:s[1]){
            int sum=0;
            for(int j:s[1])sum+=a[i][j];
            if(sum<ss[i]-sum){s[1].erase(i);s[0].ep(i);flag=false;break;}
        }
        if(flag)    break;
    }
    string ans;ans.resize(n+1);
    for(int i:s[0]) ans[i]='X';
    for(int i:s[1]) ans[i]='Y';
    for(int i=1;i<=n;i++)   printf("%c",ans[i]);
}