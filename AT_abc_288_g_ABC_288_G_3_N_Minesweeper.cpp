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
const int maxn=14,maxm=531450;
int n;
int a[maxm];
int main(){
    scanf("%d",&n);int m=pow(3,n);
    for(int i=0;i<m;i++)   scanf("%d",&a[i]);
    for(int i=1;i<m;i*=3){
        for(int j=0;j<m;j++){
            if((j/i)%3==0){
                int x=a[j],y=a[j+i],z=a[j+i+i];
                a[j]=y-z;a[j+i]=x+z-y;a[j+i+i]=y-x;
            }
        }
    }
    for(int i=0;i<m;i++)   printf("%d ",a[i]);
}