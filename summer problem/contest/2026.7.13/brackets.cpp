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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2e5+10;
int n,m,q;
int a[maxn],b[maxn],c[maxn];
char s[maxn];
int main(){
    freopen("brackets.in","r",stdin);freopen("brackets.out","w",stdout);
    scanf("%d%d",&n,&q);n<<=1;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    scanf("%s",s+1);
    int now=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='(')   now++;
        else if(!now)   b[++m]=i,now++;
        else    now--;
    }
    for(int i=b[m]+1;i<=n;i++)  c[i-b[m]]=a[i];
    sort(c+1,c+n-b[m]+1);ll ans=accumulate(c+1,c+now/2+1,0ll);
    for(int i=1;i<=n;i++){
        
    }
    while(q--){
        int i,x;scanf("%d%d",&i,&x);a[i]=x;
    }
}