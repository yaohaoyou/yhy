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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=210;
bool mem1;
int n,m;
bool a[maxn][maxn];
bool vis[maxn];
int nxt[maxn],fr[maxn];
struct DSU{
    int find(int x){while(fr[x])x=fr[x];return x;}
    inline int operator[](int x){return find(x);}
}U;
vector<int> p[maxn];
inline int id(int x){x+=n-1;return (x-1)%(n-1)+1;}
inline string ask(vector<int> &v,bool fl=true){
    printf("? ");for(int i:v)printf("%d ",i);puts("");
    fflush(stdout);
    string s;cin>>s;
    for(int i=1;i<=s.length();i++){
        if(s[i-1]=='1'){
            a[v[i-1]][v[i]]=1;
            nxt[v[i-1]]=v[i];
            if(fl&&max(v[i-1],v[i])<=n-1)   fr[v[i]]=v[i-1];
        }
    }
    return s;
}
void out(){
    // for(int i=1;i<=n;i++) debug("%d ",nxt[i]);debug("\n");
    // assert(count(nxt+1,nxt+n+1,0)==1);
    fll(vis,0,n);
    for(int i=1;i<=n;i++)if(nxt[i])vis[nxt[i]]=true;
    int x=find(vis+1,vis+n+1,0)-vis;
    printf("! ");while(x){printf("%d ",x);x=nxt[x];}puts("");
    fflush(stdout);
}
vector<int> ad(vector<int> v){
    fll(vis,0,n);
    vector<int> vq;
    for(int i:v)    vis[i]=true,vq.eb(i);
    for(int i=1;i<=n;i++)if(!vis[i])vq.eb(i);
    // assert(vq.size()==n);
    return vq;
}
bool mem2;
void matt(int _cases){
    for(int i=1;i<maxn;i++) p[i].clear();
    mems(nxt,0);mems(fr,0);mems(a,0);
    scanf("%d",&m);
    if(m==2){
        puts("? 1 2");fflush(stdout);
        string s;cin>>s;
        if(s[0]=='1')   puts("! 1 2");
        else    puts("! 2 1");
        fflush(stdout);
        return;
    }
    n=m;
    // debug("m = %d\n",m);
    if(!(m&1))  n=m-1;
    else    n=m;
    for(int i=1;i<n;i++){
        int x=i,y=i;p[i].eb(x);
        for(int j=1;;j++){
            x--;y++;
            x=id(x);y=id(y);
            p[i].eb(x);
            if(x==y)break;
            p[i].eb(y);
        }
        p[i].eb(n);
        // for(int j=0;j+1<p[i].size();j++)    a[p[i][j]][p[i][j+1]]=true;
    }
    if(!(m&1)){
        n=m;
        p[1].eb(m);
        for(int i=2;i<=n-2;i++) p[i].insert(p[i].begin(),m);
        for(int i=1;i<=n-2;i++) ask(p[i]);
        vector<int> v;
        for(int i=1;i<=n-2;i++){
            if(count(a[i]+1,a[i]+n+1,1)){
                for(int j=1;j<=n;j++)if(a[i][j]){nxt[i]=j;break;}
            }
            else    v.eb(i);
        }
        if(count(nxt+1,nxt+n+1,0)==1)   return out();
        if(a[n-1][n]){
            // for(int i=1;i<=n;i++) debug("%d ",nxt[i]);debug("\n");
            nxt[n-1]=n;
            // assert(v.size()<=1);
            if(v.size()==1&&!nxt[n]){
                vector<int> vq=ad({v[0],n});string s=ask(vq,0);
                if(s[0]=='1')   nxt[v[0]]=n;
                else    nxt[n]=U[v[0]];
            }
            return out();
        }
        if(v.empty()){
            int p=0;for(int i=1;i<=n;i++)if(a[n][i]){p=i;break;}
            if(p)   nxt[n]=p;
            else{
                auto vq=ad({n,1});string s=ask(vq);
                if(s[0]=='1')   nxt[n]=1;
                else    nxt[n]=n-1;
            }
            return out();
        }
        if(v.size()==1){
            // for(int i=1;i<=n;i++)   printf("%d ",nxt[i]);puts("");
            int x=v[0];
            auto vq=ad({x,n,U[n-1]});string s=ask(vq,0);
            if(s[0]=='1'){
                nxt[x]=n;
                if(s[1]=='1')   nxt[n]=U[n-1];
                else    nxt[n-1]=U[x];
            }
            else    nxt[n]=U[n-1],nxt[n-1]=U[x];
            return out();
        }
        // assert(v.size()==2);
        int x=v[0],y=v[1];
        vector<int> vq;//=ad({n-1,x,n,y});
        vq.eb(U[n-1]);if(vq.back()!=n-1)vq.eb(n-1);
        vq.eb(U[x]);if(vq.back()!=x)vq.eb(x);
        vq.eb(n);
        vq.eb(U[y]);if(vq.back()!=y)vq.eb(y);
        vq=ad(vq);
        string s=ask(vq,0);
        int o0=0,o1=0,o2=0;
        while(!(vq[o0]==n-1&&vq[o0+1]==U[x]))o0++;
        while(!(vq[o1]==x&&vq[o1+1]==n))o1++;
        while(!(vq[o2]==n&&vq[o2+1]==U[y]))o2++;
        if(s[o1]=='1'){
            nxt[x]=n;
            if(s[o2]=='1')   nxt[n-1]=U[x],nxt[n]=U[y];
            else    nxt[n]=U[n-1],nxt[n-1]=U[y];
        }
        else{
            if(s[o0]=='1')   nxt[y]=n,nxt[n]=U[n-1],nxt[n-1]=U[x];
            else    nxt[n-1]=U[y],nxt[y]=n,nxt[n]=U[x];
        }
        out();
    }
    else{
        for(int i=1;i<n;i++){
            string s=ask(p[i]);
            for(int j=1;j<=s.length();j++){
                if(s[j-1]=='1')   a[p[i][j-1]][p[i][j]]=true;
            }
        }
        for(int i=1;i<n;i++){
            if(count(a[i]+1,a[i]+n+1,1)){for(int j=1;j<=n;j++)if(a[i][j]){nxt[i]=j;break;}}
            else{
                int u=i;while(fr[u])u=fr[u];
                nxt[n]=u;
            }
        }
        out();
    }
    // for(int i=1;i<n;i++,puts(""))for(int j=1;j<=m;j++)printf("%d ",a[i][j]);
    // for(int i=1;i<n;i++){
    //     for(int j:p[i])printf("%d ",j);
    //     puts("");
    // }
    // puts("");
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);
}