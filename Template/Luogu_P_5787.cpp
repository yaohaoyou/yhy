//  P5787 二分图 /【模板】线段树分治
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
constexpr int maxn=3e5+10;
int n,m,k;
int U[maxn],V[maxn];
namespace DSU{
    int fa[maxn],rnk[maxn];
    stack<int> stk;
    inline int find(int x){while(x^fa[x])x=fa[x];return x;}
    inline void merge(int x,int y){if(rnk[x]>rnk[y])swap(x,y);stk.push(x);fa[x]=y;rnk[y]+=(rnk[x]==rnk[y]);}  // 将 x 合并至 y
}
using namespace DSU;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,k
    #define setmid int mid=(l+r)>>1
    vector<int> tr[maxn<<2];
    #define eb emplace_back
    void update(int p,int l,int r,int pl,int pr,int id){
        if(l>=pl&&r<=pr)    return tr[p].eb(id),void();
        setmid;
        if(pl<=mid) update(lson,pl,pr,id);
        if(pr>mid)  update(rson,pl,pr,id);
    }
    void dfs(int p,int l,int r){
        // printf("%d %d\n",l,r);
        // for(int i=1;i<=(n<<1);i++)  printf("%d %d\n",fa[i],rnk[i]);
        bool flag=true;
        int siz=stk.size();
        for(int i:tr[p]){
            int u=U[i],v=V[i],fu=find(u),fv=find(v);
            if(fu==fv){
                for(int j=l;j<=r;j++)   puts("No");
                flag=false;
                break;
            }
            merge(find(u+n),fv);merge(find(v+n),fu);
        }
        if(flag){
            if(l==r)    puts("Yes");
            else{setmid;dfs(lson);dfs(rson);}
        }
        while(stk.size()!=siz){int tp=stk.top();rnk[fa[tp]]-=(rnk[fa[tp]]==rnk[tp]);fa[tp]=tp;stk.pop();}
    }
}
using namespace SegmentTree;
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=(n<<1);i++){fa[i]=i;rnk[i]=1;}
    for(int i=1;i<=m;i++){
        int l,r;
        scanf("%d%d%d%d",&U[i],&V[i],&l,&r);
        if(l+1<=r) update(all,l+1,r,i);
    }
    dfs(all);
}