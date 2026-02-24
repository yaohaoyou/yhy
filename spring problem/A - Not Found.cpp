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
char s[30];
int main(){
    scanf("%s",s+1);
    int n=strlen(s+1);
    for(char a='a';a<='z';a++){
        bool f=false;
        for(int i=1;i<=n;i++)   f|=(s[i]==a);
        if(!f)  exit(putchar(a)&0);
    }
}