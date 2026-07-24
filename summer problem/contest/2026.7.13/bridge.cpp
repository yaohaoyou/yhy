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
const int maxn=100;
int n;
string a;
int buc[10];
void input(){getline(cin,a);n=a.length();a=' '+a;}
int op(char c){if(c=='J')return 1;if(c=='Q')return 2;if(c=='K')return 3;if(c=='A')return 4;return 0;}
int calc(){int res=0;for(int i=1;i<=n;i++)res+=op(a[i]);return res;}
void matt(int _cases){
    mems(buc,0);
    int res=40,TT=8;
    while(TT--){
        input();res-=calc();
        for(int i=1;i<=n;i++)if(op(a[i]))buc[op(a[i])]++;
    }
    int now=0,x=13;
    for(int i=4;i;i--){now+=min(4-buc[i],x)*i,x-=min(4-buc[i],x);}
    printf("%d %d\n",res-now,now);
}
int main(){freopen("bridge.in","r",stdin);freopen("bridge.out","w",stdout);int T;cin>>T;getline(cin,a);for(int i=1;i<=T;i++)matt(i);}