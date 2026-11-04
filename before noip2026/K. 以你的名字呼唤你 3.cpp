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
const int maxn=2e6+10;
bool mem1;
int n;
char f[maxn];
char a[maxn];
inline bool is_lyndon(int x){
    if(x==n)return true;
    int i=x;
    int j=x,k=x+1;
    for(;k<=n;k++){
        if(a[j]==a[k])  j++;
        else if(a[k]>a[j])  j=x;
        else    return false;
    }
    if(i<=j) i+=k-j;
    return i==n+1;
}
vector<int> out;
bool slv(int x){
    if(x==n)    return false;
    if(!is_lyndon(x))   return out.eb(n),true;
    assert(a[n]!=a[x]);
    vector<pii> v;
    for(int i=x;i<=n;i++)if(a[i]==a[x]){
        int j=i;while(j<=n&&a[j]==a[x])j++;
        v.eb(i,j-1);
        i=j-1;
    }
    if(v.size()>=3){
        out.eb(v[1].se);
        return slv(v[1].se+1);
    }
    if(v.size()==2&&v[0].se!=x){
        out.eb(v[0].se);
        out.eb(n);
        return true;
    }
    if(v.size()==1&&v[0].se==x) return false;
    if(v.size()==1){out.eb(v[0].se);return slv(v[0].se+1);}
    assert(v.size()==2&&v[0].se==x);
    int i=v.back().se;
    for(int j=x;i<=n;i++,j++){
        if(a[i]!=a[j])  break;
        if(f[i+1]!=a[i+1]){out.eb(i);return slv(i+1);}
    }
    int p=i;while(p>1&&a[p-1]==a[i])p--;
    out.eb(p-1);return slv(p);
    // out.eb(v.back().se);return slv(v.back().se+1);
}
int T;
bool mem2;
void matt(int _cases){
    scanf("%s",a+1);n=strlen(a+1);
    // if(T==159725&&_cases==972){
    //     for(int i=1;i<=n;i++)putchar(a[i]);puts("");
    // }
    f[n]=a[n];
    for(int i=n-1;i;i--)  f[i]=min(f[i+1],a[i]);
    out.clear();
    if(slv(1)){
        puts("Yes");printf("%d\n",out.size());
        for(int i:out)printf("%d ",i);puts("");
    }
    else    puts("No");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}