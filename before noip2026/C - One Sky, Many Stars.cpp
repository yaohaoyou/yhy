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
const int maxn=2e5+10;
bool mem1;
int n,q,now;
bool L[maxn],R[maxn];
pii a[maxn];
void chkL(int x){
    now-=(L[x]&&R[x]);
    int p=a[x].fi-a[x].se,l=a[x-1].fi-a[x-1].se,r=a[x-1].fi+a[x-1].se;
    L[x]=(x!=1&&p>l&&p<r);
    l=a[x+1].fi-a[x+1].se,r=a[x+1].fi+a[x+1].se;
    L[x]|=(x!=n&&p>l&&p<r);
    now+=(L[x]&&R[x]);
}
void chkR(int x){
    now-=(L[x]&&R[x]);
    int p=a[x].fi+a[x].se,l=a[x+1].fi-a[x+1].se,r=a[x+1].fi+a[x+1].se;
    R[x]=(x!=n&&p>l&&p<r);
    l=a[x-1].fi-a[x-1].se,r=a[x-1].fi+a[x-1].se;
    R[x]|=(x!=1&&p>l&&p<r);
    now+=(L[x]&&R[x]);
}
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].fi);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].se);
    for(int i=1;i<=n;i++)   chkL(i),chkR(i);
    now=0;for(int i=1;i<=n;i++)now+=(L[i]&&R[i]);
    scanf("%d",&q);
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        a[x].se=y;
        chkL(x);chkR(x);if(x^n)chkL(x+1),chkR(x+1);if(x^1)chkL(x-1),chkR(x-1);
        puts(now?"No":"Yes");
    }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}