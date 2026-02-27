#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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
using namespace __gnu_pbds;
const int maxn=1e5+10;
int n,q;
char a[maxn];
vector<pii> Q[maxn];
char ans[maxn];
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> tr;
struct st{
    int Log[maxn];
    pii st[20][maxn];
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=pii(a[i],-i);
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline pii query(int l,int r){int k=Log[r-l+1];return max(st[k][l],st[k][r-(1<<k)+1]);}
}st;
bool used[maxn];
int main(){
    scanf("%s%d",a+1,&q);n=strlen(a+1);
    st.build();
    for(int i=1;i<=q;i++){
        int k,l;scanf("%d%d",&k,&l);
        Q[k].eb(l,i);
    }
    int hd,en=n+1;
    stack<int> stk;stk.ep(0);
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&en<=stk.top())  stk.pop();
        hd=stk.top();
        int x=-st.query(hd+1,en-1).se;
        tr.insert(x);used[x]=true;stk.ep(x);
        while(en>0&&used[en-1]) en--;
        for(auto [j,id]:Q[i])   ans[id]=a[*tr.find_by_order(j-1)];
    }
    for(int i=1;i<=q;i++)   printf("%c",ans[i]);
}