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
const int maxn=1e5+10,V=1e5,B=320;
int n,q;
int a[maxn];
map<pii,int> ans;
vector<int> v[maxn][2],vec;
inline void getmn(auto &x,auto y){(x>y)&&(x=y);}
inline int calc(int x,int y){
    for(int i=1;i<=n;i++){
        
    }
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        v[a[i]][0].eb(i);
    }
    for(int i=1;i<=V;i++)if(v[i][0].size()>B)v[i][0].swap(v[i][1]),vec.eb(i);
    for(int i:vec){
        for(int j:vec){
            ans[pii(i,j)]=calc(i,j);
        }
    }
    int lst=0;
    while(q--){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);x^=lst;y^=lst;
        if(op==1){
            merge(v[x][0].begin(),v[x][0].end(),v[y][0].begin(),v[y][0].end(),v[y][0]);
            v[x][0].clear();
            if(v[y][0].size()>B)    merge(v[y][0].begin(),v[y][0].end(),v[y][1].begin(),v[y][1].end(),v[y][1]),v[y][0].clear();
            if(!v[x][1].empty())    merge(v[x][1].begin(),v[x][1].end(),v[y][1].begin(),v[y][1].end(),v[y][1]);
            v[x][1].clear();
        }
        else{

        }
    }
}