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
int n;
string s="HelloWorld";
int main(){
    scanf("%d",&n);
    for(int i=0;i<s.length();i++){
        if(i+1!=n)  putchar(s[i]);
    }
}