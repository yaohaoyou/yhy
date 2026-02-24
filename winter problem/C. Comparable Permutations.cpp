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
#define NO return puts("! -1"),fflush(stdout),void()
const int maxn=2e4+10;
int n,a[maxn],b[maxn];
// inline int ask(int i,int j){printf("? %d %d\n",i,j);fflush(stdout);int x;scanf("%d",&x);return x;}
inline int ask(int i,int j){return b[i]<b[j];}
void matt(int _cases){
    scanf("%d",&n);iota(a+1,a+n+1,1);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    int p=n;while(p>1&&ask(p-1,p))  p--;
    if(p==1)    NO;
    int q=p;while(q>1&&!ask(q-1,q)) q--;
    if(q==1)    NO;
    int x=q;
    while(x<=p&&ask(q-1,x)) x++;x--;
    swap(a[x],a[q-1]);
    reverse(a+q,a+p+1);
    int k=p+1,y=q;
    while(k<=n&&!ask(a[k-1],k)){
        while(ask(a[y],k))y++;
        for(int i=k-1;i>=y;i--)   swap(a[i],a[i+1]);
        k++;
    }
    printf("! ");for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");fflush(stdout);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
// 