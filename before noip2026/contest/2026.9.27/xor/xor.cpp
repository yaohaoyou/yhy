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
const int maxn=2e5+10,d[4]={0,2,3,1};
bool mem1;
int n;
vector<int> ans[maxn];
int a[maxn];
bitset<maxn> f,g;
bool chk(){
    set<int> s;
    for(int i=0;i<n;i++)if((a[i]^i)>=n)return 0;else s.ep(a[i]^i);
    return s.size()==n;
}
bool dfs(int x){
    if(x==n){
        // puts("Yes");
        // for(int i=0;i<n;i++)printf("%d ",i);puts("");
        // for(int i=0;i<n;i++)printf("%d ",a[i]);puts("");
        for(int i=0;i<n;i++)ans[n].eb(a[i]);
        // assert(chk());
        return true;
    }
    for(int i=d[x&3];i<n;i+=4)if(!f[i]&&!g[i^x]){
        a[x]=i;
        // f[i]=g[i^x]=true;
        f.set(i);g.set(i^x);
        if(dfs(x+1)){
            // f[i]=g[i^x]=false;
            f.reset(i);g.reset(i^x);
            return true;
        }
        f.reset(i);g.reset(i^x);
    }
    return false;
}
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    if(n<=10){
        if(n==1){puts("Yes");puts("0");puts("0");}
        if(n==2)puts("No");
        if(n==3)puts("No");
        if(n==4){puts("Yes");puts("0 1 2 3");puts("0 2 3 1");}
        if(n==5)puts("No");
        if(n==6)puts("No");
        if(n==7)puts("No");
        if(n==8){puts("Yes");puts("0 1 2 3 4 5 6 7");puts("0 2 4 6 3 1 7 5");}
        if(n==9)puts("No");
        if(n==10)puts("No");
        return;
    }
    // if(!ans[n].empty()){
        puts("Yes");
        for(int i=0;i<n;i++)printf("%d ",i);puts("");
        for(int i=0;i<n;i++)printf("%d ",a[i]=ans[65536][i]);puts("");
        // for(int i=0;i<n;i++)printf("%d ",a[i]^i);puts("");
        // assert(chk());
        // for(int i:ans[n])   printf("%d ",i);puts("");
        return;
    // }
    if(!dfs(0)) puts("No");
    else{
        puts("Yes");
        for(int i=0;i<n;i++)printf("%d ",i);puts("");
        for(int i:ans[n])   printf("%d ",i);puts("");
    }
    // printf("if(n==%d)puts(\"No\");\n",n);
}
int main(){
    freopen("xor.in","r",stdin);freopen("xor.out","w",stdout);
    n=65536;
    assert(dfs(0));
    // return 0;
    // for(int i=1;i<maxn;i<<=2)   n=i,assert(dfs(0));
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);
}