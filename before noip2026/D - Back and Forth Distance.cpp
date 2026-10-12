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
bool mem1;
const int maxn=3e5+10;
int n,q;
int l[maxn],r[maxn],p[maxn],s[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=2;i<=n;i++)   scanf("%d",&l[i]);
    l[1]=r[n]=s[n+1]=p[0]=1e9;
    for(int i=1;i<n;i++)    scanf("%d",&r[i]),p[i]=min(p[i-1],r[i]);
    for(int i=n;i;i--)  s[i]=min(s[i+1],l[i]);
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        int ans=0;
        if(x<y) ans=min(r[x],l[x]+p[x]);
        else    ans=min(l[x],r[x]+s[x]);
        printf("%d\n",ans);
    }
}