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
string a,b,c;
void matt(){
    cin>>n>>a>>m>>b>>c;
    for(int i=0;i<m;i++){
        if(c[i]=='D')   a+=b[i];
        else    a=b[i]+a;
    }
    cout<<a<<endl;
}
int main(){int T;cin>>T;while(T--)matt();}