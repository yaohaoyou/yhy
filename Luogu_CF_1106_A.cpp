#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=510;
int n;
char s[maxn][maxn];
int ans;
bool check(int x,int y){
    if(s[x][y]!='X')    return false;
    if(s[x-1][y+1]!='X')    return false;
    if(s[x-1][y-1]!='X')    return false;
    if(s[x+1][y+1]!='X')    return false;
    if(s[x+1][y-1]!='X')    return false;
    return true;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    for(int i=2;i<n;i++){
        for(int j=2;j<n;j++){
            ans+=check(i,j);
        }
    }
    printf("%d\n",ans);
}