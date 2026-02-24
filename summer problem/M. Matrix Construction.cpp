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
const int maxn=1010,dir[2][2]={{1,0},{0,1}};
int n,m;
int a[maxn][maxn],b[maxn*maxn];
unordered_set<int> st;
bool check(){
    st.clear();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<2;k++){
                int x=i+dir[k][0],y=j+dir[k][1];
                if(x<=0||x>n||y<=0||y>m)continue;
                if(st.find(b[a[i][j]]+b[a[x][y]])!=st.end())  return false;
                st.ep(b[a[i][j]]+b[a[x][y]]);
            }
        }
    }
    return true;
}
void matt(){
    scanf("%d%d",&n,&m);
    int tot=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=++tot;
    tot=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[a[i][j]]=++tot;
    while(!check())  random_shuffle(b+1,b+tot+1);
    puts("Yes");
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++)printf("%d ",b[a[i][j]]);
}
int main(){srand(time(0));int T;scanf("%d",&T);while(T--)matt();}