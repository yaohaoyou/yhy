#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10;
int n;
int s1,s2;
int a[maxn],b[maxn];
int ans,out;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    for(int i=1;i<=n;i++)   s1+=a[i];
    for(int i=1;i<=n;i++)   s2+=b[i];
    ans=abs(s1-s2);
    for(int i=1;i<=n;i++){
        s1-=a[i];s2-=b[i];
        s1+=b[i];s2+=a[i];
        if(abs(s1-s2)>ans){ans=abs(s1-s2);out=i;}
        s1+=a[i];s2+=b[i];
        s1-=b[i];s2-=a[i];
    }
    printf("%d\n",out);
}