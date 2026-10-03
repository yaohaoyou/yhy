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
const int maxn=1010;
bool mem1;
int n,mx;
// int a[maxn],b[maxn];
vector<int> a,b;
queue<vector<int>> q;
map<vector<int>,int> mp;
bool mem2;
void matt(int _cases){
    while(!q.empty())q.pop();
    mp.clear();
    scanf("%d",&n);
    a.resize(n+1);b.resize(n+1);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    // for(int i=1;i<=n;i++)   scanf("%1d",&b[i]);
    mp[a]=0;q.ep(a);
    while(!q.empty()){
        auto c=q.front();q.pop();
        // if(b==c)    break;
        int now=mp[c];
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                bool fl=true;
                for(int x=i,y=j;x<y;x++,y--)if(c[x]^c[y]){fl=false;break;}
                if(!fl) continue;
                for(int k=i;k<=j;k++)c[k]^=1;
                if(mp.find(c)==mp.end()){mp[c]=now+1;q.ep(c);}
                for(int k=i;k<=j;k++)c[k]^=1;
            }
        }
    }
    for(auto [i,j]:mp)  gmx(mx,j);
    // if(mx==8)   exit(printf("max = %d\n",mx)&0);
    // if(cnt>4&&mp[b]==4){
    //     for(int i=1;i<=n;i++)printf("%d",a[i]);puts("");
    //     for(int i=1;i<=n;i++)printf("%d",b[i]);puts("");
    //     exit(0);
    // }
    // gmx(mx,mp[b]);
    // printf("%d\n",mp[b]);
}
void data(int n){
    int T=(1<<n);
    printf("%d\n",T);
    for(int i=0;i<1<<n;i++){
        printf("%d\n",n);
        for(int x=1;x<=n;x++)printf("%d",bool(i&(1<<x-1)));puts("");
        // for(int y=1;y<=n;y++)printf("%d",bool(j&(1<<y-1)));puts("");
    }
    exit(0);
}
int main(){
    // data(6);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);
    printf("max = %d\n",mx);
}