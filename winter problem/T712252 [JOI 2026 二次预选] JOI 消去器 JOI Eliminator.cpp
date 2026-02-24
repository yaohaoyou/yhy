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
const int maxn=5e5+10;
int n;
char a[maxn];
int main(){
    scanf("%d%s",&n,a+1);
    int x=0,y=0;
    for(int i=1;i<=n;i++){
        if(i<n&&a[i]=='O'&&a[i+1]=='I'){i++;x++;continue;}
        if(a[i]=='J'){y++;continue;}
        while(x--)printf("OI");
        while(y--)printf("J");
        x=y=0;
        printf("%c",a[i]);
    }
    while(x--)printf("OI");
    while(y--)printf("J");
}