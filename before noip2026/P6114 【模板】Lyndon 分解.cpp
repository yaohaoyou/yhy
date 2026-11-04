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
bool mem1;
const int maxn=5e6+10;
int n;
char a[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%s",a+1);n=strlen(a+1);
    int ans=0;
    for(int i=1;i<=n;){
        int j=i,k=i+1;
        for(;k<=n;k++){
            if(a[j]==a[k])  j++;
            else if(a[k]>a[j])  j=i;
            else    break;
        }
        while(i<=j) i+=k-j,ans^=i-1;
    }
    printf("%d\n",ans);
}