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
const int maxn=2e7+10;
int n,m;
char a[maxn],b[maxn];
int nxt[maxn],ext[maxn];
int main(){
    scanf("%s%s",a+1,b+1);n=strlen(a+1);m=strlen(b+1);
    int p=0;ll ans=0;
    nxt[1]=m;
    nxt[2]=0;while(2+nxt[2]<=m&&b[2+nxt[2]]==b[1+nxt[2]])nxt[2]++;p=2;
    for(int i=3;i<=m;i++){
        int x=p+nxt[p]-1;
        // printf("x-i+1 = %d %d\n",i+nxt[i-p+1]-1,x);
        if(i+nxt[i-p+1]<=x)   nxt[i]=nxt[i-p+1];
        else{
            nxt[i]=max(0,x-i+1);
            while(i+nxt[i]<=m&&b[i+nxt[i]]==b[1+nxt[i]])nxt[i]++;
            p=i;
        }
    }
    // for(int i=1;i<=m;i++)   printf("%d ",nxt[i]);puts("");
    for(int i=1;i<=m;i++)   ans^=(1ll*i*(nxt[i]+1));
    printf("%lld\n",ans);
    p=1;
    ext[1]=0;while(ext[1]<n&&ext[1]<m&&a[ext[1]+1]==b[ext[1]+1])ext[1]++;
    for(int i=2;i<=n;i++){
        int x=p+ext[p]-1;
        if(i+nxt[i-p+1]<=x)   ext[i]=nxt[i-p+1];
        else{
            ext[i]=max(0,x-i+1);
            while(i+ext[i]<=n&&1+ext[i]<=m&&a[i+ext[i]]==b[1+ext[i]])   ext[i]++;
            p=i;
        }
    }
    ans=0;
    for(int i=1;i<=n;i++)   ans^=(1ll*i*(ext[i]+1));
    printf("%lld\n",ans);
}