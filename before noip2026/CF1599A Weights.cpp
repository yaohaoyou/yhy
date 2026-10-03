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
const int maxn=1e6+10;
int n;
int a[maxn];
char s[maxn];
vector<int> ans;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    scanf("%s",s+1);
    sort(a+1,a+n+1);
    for(int i=n,l=1,r=n;i;i--){
        if(l==r)    ans.eb(l);
        else if(s[i]!=s[i-1])   ans.eb(r--);
        else    ans.eb(l++);
    }
    reverse(ans.begin(),ans.end());
    if(s[n]=='L'){
        for(int i:ans){
            printf("%d ",a[i]);
            if((i&1)==(n&1)) puts("L");
            else puts("R");
        }
    }
    else{
        for(int i:ans){
            printf("%d ",a[i]);
            if((i&1)==(n&1)) puts("R");
            else puts("L");
        }
    }
}