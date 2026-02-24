#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1010;
int n,x;
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int x,y;
        scanf("%d%d",&x,&y);
        if(x&1) printf("%d %d\n",y,1);
        else    printf("%d %d\n",1,y);
    }
}