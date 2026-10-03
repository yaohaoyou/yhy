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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1030,B=14,maxv=(1<<B)+10;
bool mem1;
vector<pii> mp[maxn][maxn];
bool rev[B+2][maxv];
namespace Baoli{
    queue<int> q;
    void solve(int a,int n){
        while(!q.empty())q.pop();
        q.ep(a);
        while(!q.empty()){
            auto c=q.front();q.pop();
            vector<pii> dp=mp[a][c];
            for(int i=0;i<n;i++){
                for(int j=i+1;j<n;j++){
                    bool fl=true;
                    for(int x=i,y=j;x<y;x++,y--)if(bool(c&(1<<x))^bool(c&(1<<y))){fl=false;break;}
                    if(!fl) continue;
                    for(int k=i;k<=j;k++)c^=1<<k;
                    if((c^a)&&mp[a][c].empty()){mp[a][c]=dp;mp[a][c].eb(i,j);q.ep(c);}
                    for(int k=i;k<=j;k++)c^=1<<k;
                }
            }
        }
    }
    vector<pii> f[maxv];
    vector<pii> solve(int a,int b,int n){
        if(a==b)    return vector<pii>();
        while(!q.empty())f[q.front()].clear(),q.pop();
        q.ep(a);
        while(!q.empty()){
            auto c=q.front();q.pop();
            vector<pii> dp=f[c];f[c].clear();
            for(int i=0;i<n;i++){
                for(int j=i+1;j<n;j++){
                    bool fl=true;
                    int rv=(c&((1<<j+1)-1))>>i;
                    if(!rev[j-i+1][rv])    continue;
                    int flp=(((1<<j+1)-1)>>i)<<i;
                    c^=flp;
                    if((c^a)&&f[c].empty()){
                        f[c]=dp;f[c].eb(i,j);
                        q.ep(c);
                        if(c==b)    return f[c];
                    }
                    c^=flp;
                }
            }
        }
        assert(0);
        return vector<pii>();
    }
}
int n;
int a[maxn],b[maxn];
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%1d",&b[i]);
    if(n<=10){
        vector<pii> ans;
        int x=0,y=0;
        for(int i=1;i<=n;i++)if(a[i])x|=1<<i-1;
        for(int i=1;i<=n;i++)if(b[i])y|=1<<i-1;
        ans=Baoli::solve(x,y,n);
        printf("%d\n",ans.size());
        for(auto [i,j]:ans) printf("%d %d\n",i+1,j+1);
        return;
    }
    vector<pii> v;
    for(int i=1;i<=n;i+=10) v.eb(i,min(n,i+9));
    if(n%10&&n%10<=B%10){
        int l,x,y;
        y=v.back().se-v.back().fi+1;v.pop_back();
        l=v.back().fi;x=v.back().se-v.back().fi+1;v.pop_back();
        v.eb(l,n);
    }
    vector<pii> ans;ans.clear();
    for(auto [l,r]:v){
        int x=0,y=0;
        for(int i=l;i<=r;i++)if(a[i])x|=1<<i-l;
        for(int i=l;i<=r;i++)if(b[i])y|=1<<i-l;
        if(r-l+1==10){
            for(auto [i,j]:mp[x][y])    ans.eb(i+l,j+l);
        }
        else{
            vector<pii> now=Baoli::solve(x,y,r-l+1);
            for(auto [i,j]:now)    ans.eb(i+l,j+l);
        }
    }
    printf("%d\n",ans.size());
    for(auto [i,j]:ans) printf("%d %d\n",i,j);
}
void data(){
    srand(time(0));
    int T=1000;
    printf("%d\n",T);
    while(T--){
        n=rand()%997+4;
        printf("%d\n",n);
        for(int i=1;i<=n;i++)   printf("%d",rand()%2);puts("");
        for(int i=1;i<=n;i++)   printf("%d",rand()%2);puts("");
    }
    exit(0);
}
int main(){
    for(int i=2;i<=B;i++){
        for(int j=0;j<1<<i;j++){
            rev[i][j]=true;
            for(int x=0,y=i-1;x<y;x++,y--)if(bool(j&(1<<x))^bool(j&(1<<y))){rev[i][j]=false;break;}
        }
    }
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    for(int i=0;i<1024;i++)Baoli::solve(i,10);
    int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);
}