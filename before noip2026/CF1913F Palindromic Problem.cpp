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
bool mem1;
const int maxn=6e5+10;
int n,m;
char a[maxn],b[maxn];
int p[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%s",&m,b+1);
    a[++n]='~';
    for(int i=1;i<=m;i++)   a[++n]='|',a[++n]=b[i];
    a[++n]='|';
    for(int i=1,r=0,mid=0;i<=n;i++){
        p[i]=i<r?min(r-i+1,p[(mid<<1)-i]):1;
        while(a[i+p[i]]==a[i-p[i]]) p[i]++;
        if(i+p[i]>r)    r=i+p[i]-1,mid=i;
        
    }
}