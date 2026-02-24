#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1010;
int n,m,q;
namespace DSU{
    int fa[maxn<<1],siz[maxn<<1];
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void init(){for(int i=1;i<=n<<1;i++)fa[i]=i,siz[i]=1;}
    void merge(int x,int y){
        if(find(x)==find(y))    return;
        x=find(x);y=find(y);
        siz[x]+=siz[y];
        fa[y]=x;
    }
}
using namespace DSU;
// int tot;
// void dfs(int l,int r){
//     if(l>r) return;
//     if(r-l+1==2){ 
//         cout<<"? "<<l<<' '<<r<<endl;
//         tot++;
//         int x;cin>>x;
//         if(x)   merge(l+n,r),merge(l,r+n);
//         else    merge(l,r),merge(l+n,r+n);
        
//         return;
//     }
//     int mid=(l+r)>>1;
//     if((mid-l+1)&1) mid++;
//     cout<<"? "<<l<<' '<<r<<endl;
//     tot++;
//     int x;cin>>x;
//     if(x)   merge(l+n,r),merge(l,r+n);
//     else    merge(l,r),merge(l+n,r+n);
//     dfs(l,mid);dfs(mid+1,r);
// }
int fuck[maxn];
int rea;
int tot,cnt,out;
int a[maxn];
bool f[maxn];
vector<int> v[20];
int ans[20];
inline int ask(int x,int y){
    cout<<"? "<<x<<' '<<y<<endl;
    // int zwx=fuck[x]!=fuck[y];return zwx;
    int zwx;
    cin>>zwx;
    return zwx;
}
int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=10;i++)  fuck[i]=1;
    for(int i=1;i<=90;i++){
        for(int j=1;j<=11;j++)  a[j]=++tot;
        bool fl=1;
        for(int j=2;j<=11;j++){
            f[a[j]]=ask(a[1],a[j]);
            if(f[a[j]])   fl=0;
        }
        if(!fl){cnt++;for(int j=1;j<=11;j++)  v[cnt].eb(a[j]);}
        else if(!rea)    rea=a[1];
    }
    for(int i=1;i+1<=cnt;i+=2){
        vector<int> vv[4];vv[0].clear();vv[1].clear();vv[2].clear();vv[3].clear();
        for(int j:v[i])vv[f[j]].eb(j);
        if(vv[0].size()<vv[1].size())   swap(vv[0],vv[1]);
        for(int j:v[i+1])vv[f[j]+2].eb(j);
        if(vv[2].size()<vv[3].size())   swap(vv[2],vv[3]);
        int x=vv[0][0],y=vv[2][0];
        bool o=ask(x,y);
        if(o){
            if(vv[0].size()+vv[3].size()>=11){
                for(int j:vv[1]) ans[++out]=j;
                for(int j:vv[2]) ans[++out]=j;
            }
            else{
                for(int j:vv[0]) ans[++out]=j;
                for(int j:vv[3]) ans[++out]=j;
            }
        }
        else{
            if(vv[0].size()+vv[2].size()>=11){
                for(int j:vv[1]) ans[++out]=j;
                for(int j:vv[3]) ans[++out]=j;
            }
            else{
                for(int j:vv[0]) ans[++out]=j;
                for(int j:vv[2]) ans[++out]=j;
            }
        }
    }
    // puts("nboj");
    vector<int> lst;lst.clear();
    if(cnt&1) for(int i:v[cnt]) lst.eb(i);
    for(int i=991;i<=1000;i++) lst.eb(i);
    for(int i:lst)
        if(ask(rea,i))  ans[++out]=i;
    cout<<"! ";
    for(int i=1;i<=m;i++) cout<<ans[i]<<' ';
    cout<<endl;
}