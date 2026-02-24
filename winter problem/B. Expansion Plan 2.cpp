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
const int maxn=2e5+10;
int n,x,y;
char s[maxn];
void matt(int _cases){
    scanf("%d%d%d%s",&n,&x,&y,s+1);
    x=abs(x);y=abs(y);
    for(int i=1;i<=n;i++){
        if(s[i]=='8')   x--,y--;
        else{
            if(x<y) y--;
            else x--;
        }
        x=max(x,0);y=max(y,0);
    }
    puts((!x&&!y)?"YES":"NO");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}