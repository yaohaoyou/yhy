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
const int maxn=610;
int n;
int a[maxn];
set<int> st;
int query(vector<int> ask){printf("? %d ",ask.size());for(int j:ask) printf("%d ",j);puts("");fflush(stdout);int x;scanf("%d",&x);return x;}
void matt(int _cases){
    st.clear();for(int i=1;i<=n+n;i++)a[i]=0;
    scanf("%d",&n);
    for(int i=2;i<=n+n;i++){
        vector<int> ask;ask.clear();
        for(int j=1;j<=i;j++)if(!st.count(j))ask.eb(j);
        int x=query(ask);
        if(x)   a[i]=x,st.ep(i);
    }
    st.clear();
    for(int i=n+n-1;i;i--){
        if(a[i])    continue;
        vector<int> ask;ask.clear();
        for(int j=i;j<=n+n;j++)if(!st.count(j))ask.eb(j);
        int x=query(ask);
        if(x)   a[i]=x,st.ep(i);
    }
    printf("! ");for(int i=1;i<=n+n;i++)printf("%d ",a[i]);fflush(stdout);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}