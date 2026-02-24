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
#define uint unsigned int
uint seed;
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
int n;
uint a[maxn],b[maxn];
bool ntpri[maxn];
int main(){
    cin>>n>>seed;
    for(int i=1;i<=n;i++)   a[i]=getnext();
    for(int i=2;i<=n;i++){
        if(ntpri[i])   continue;
        for(int j=i;j<=n;j+=i){
            ntpri[j]=true;
            a[j]+=a[j/i];
        }
    }
    uint ans=0;
    for(int i=1;i<=n;i++)   ans^=a[i];
    cout<<ans;
}