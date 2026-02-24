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
const int maxn=2e6+10;
int n;
int nxt[maxn],s[maxn];
char a[maxn];
int main(){
    scanf("%s",a+1);n=strlen(a+1);
    int p=0;
    nxt[1]=n;nxt[2]=0;while(2+nxt[2]<=n&&a[2+nxt[2]]==a[1+nxt[2]])nxt[2]++;
    for(int i=3;i<=n;i++){
        int x=p+nxt[p]-1;
        if(i+nxt[i-p+1]<=x)   nxt[i]=nxt[i-p+1];
        else{
            nxt[i]=max(0,x-i+1);
            while(i+nxt[i]<=n&&a[i+nxt[i]]==a[1+nxt[i]])nxt[i]++;
            p=i;
        }
    }
    for(int i=1;i<=n;i++)   s[nxt[i]]++;s[0]=0;
    for(int i=n;i;i--)  s[i]+=s[i+1];
    for(int i=1;i<=n;i++)   printf("%d ",s[nxt[i]]);
}