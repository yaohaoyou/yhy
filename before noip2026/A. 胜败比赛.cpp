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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
int a,b;
bool mem2;
void matt(int _cases){
    scanf("%d%d",&a,&b);
    if(a==1||b==1)  return printf("%d\n",a-b),void();
    a--;
    int x=a;
    while(x&&b>1){
        int o=b&1;b-=o;
        b>>=1;b+=o;
        x--;
    }
    a=1;
    if(b==1)    a+=x;
    else{
        for(int i=1;i<=x;i++){
            a++;int g=__gcd(a,b);
            a/=g;b/=g;
        }
    }
    printf("%d\n",a-b);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}