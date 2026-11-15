#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
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
bool mem1;
const int maxn=1e7+10,bs=20261114;
int n,ans=0;
// int a[maxn];
bool f[maxn];
unordered_set<ull> s;//,out;
ull Hash(vector<int> &A){
    ull res=0;
    for(int i:A)res=res*bs+i;
    return res;
}
bool is_perm(vector<int> &A){
    for(int i:A)f[i]=true;
    bool ret=count(f+1,f+n+1,1)==n;
    for(int i:A)f[i]=false;
    return ret;
}
void dfs(vector<int> a){
    ull H=Hash(a);
    if(s.find(H)!=s.end())  return;
    s.ep(H);
    ans+=is_perm(a);
    // if(is_perm(a))  out.ep(a);
    bool fl=false;
    for(int i=0;i<n;i++){
        int j=(i+1)%n,k=(i+2)%n;
        if(a[i]==a[j]&&a[i]==a[k]){
            for(int x=1;x<=n;x++){
                for(int y=1;y<=n;y++){
                    for(int b:{i,j,k})for(int c:{i,j,k})if(b^c){
                        fl=true;
                        swap(a[b],x);swap(a[c],y);
                        dfs(a);
                        swap(a[b],x);swap(a[c],y);
                    }
                }
            }
        }
    }
    
    // for(int i:a)f[i]=true;
    // if(fl&&count(f+1,f+n+1,1)==n-2){
    //     out.ep(a);
    // }
    // for(int i:a)f[i]=false;
}
bool mem2;
int main(){
    freopen("fx.in","r",stdin);freopen("fx.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    vector<int> a;
    scanf("%d",&n);a.resize(n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i-1]);
    if(is_perm(a))  return puts("1"),0;
    if(n>4){
        int ans=1;for(int i=1;i<=n;i++)ans=1ull*ans*i%998244353;
        printf("%d\n",ans);return 0;
    }
    dfs(a);
    printf("%d\n",ans);
    // for(auto a:out){for(int i:a)printf("%d ",i);puts("");}
}