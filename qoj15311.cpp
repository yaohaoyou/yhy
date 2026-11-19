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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=5e5+10;
bool mem1;
int n;
int a[maxn];
struct ST{
    pii st[20][maxn];
    void build(){
        int lg=31^__builtin_clz(n);
        for(int i=1;i<=n;i++)st[0][i]=pii(a[i],-i);
        for(int i=1;i<=lg;i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    pii query(int l,int r){if(l>r)return pii(n+n,0);int k=31^__builtin_clz(r-l+1);return min(st[k][l],st[k][r-(1<<k)+1]);}
}st[2];
char ans[maxn];
int R[maxn];
stack<int> s[2];
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i+=2)  a[i]+=n;
    st[0].build();
    for(int i=1;i<=n;i+=2)  a[i]-=n;
    for(int i=2;i<=n;i+=2)  a[i]+=n;
    st[1].build();
    for(int i=2;i<=n;i+=2)  a[i]-=n;
    for(int i=1;i<=n;i++){
        bool o=(i-1)&1;
        if(!s[o].empty()){
            int pr=s[o].top();
            if(a[i]==a[R[pr]]&&a[pr]<=st[o].query(i+1,R[pr]-1).fi)  ans[pr]='(',ans[i]=')',s[o].pop();
            else{
                R[i]=-st[o].query(i+1,R[pr]-1).se;
                s[i&1].ep(i);
            }
        }
        else{
            R[i]=-st[o].query(i+1,n).se;
            s[i&1].ep(i);
        }
    }
    // for(int i=1;i<=n;i++)   printf("%d ",R[i]);puts("");
    // printf("%d %d\n",s[0].top(),s[1].top());
    assert(s[0].empty()&&s[1].empty());
    for(int i=1;i<=n;i++)   putchar(ans[i]);puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}