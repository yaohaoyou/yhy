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
const int maxn=110;
int n,m;
string a[maxn],s;
bool f[30];
void matt(int _cases){
    mems(f,0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)   cin>>a[i],f[a[i][0]-'a']=true;
    bool flag=true;
    while(m--){
        cin>>s;
        for(char c:s)flag&=f[c-'A'];
        f[s[0]-'A']=true;
    }
    puts(flag?"YES":"NO");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}