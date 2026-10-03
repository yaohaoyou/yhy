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
bool mem1;
const int maxn=1010;
int n,X,Y,lgV=10,lglgV=4;
vector<vector<int>> ans;
int c[maxn],a[maxn];
void getdata(){
    int i=0;
    for(vector<int>v:ans){
        i++;
        bool flag=true;
        for(int x:v)if(x==X)flag=false;
        if(i==Y)flag^=1;
        a[i-1]=flag;
    }
}
bool mem2;
int main(){
    // scanf("%d%d",&X,&Y);
    // srand(chrono::system_clock::now().time_since_epoch().count());
    // n=rand()%1000+1;X=rand()%n+1;Y=rand()%15+1;debug("%d %d %d\n",n,X,Y);
    // debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%*d",&n);
    if(n==1){
        puts("2");fflush(stdout);
        puts("1");fflush(stdout);
        return 0;
    }
    if(n<=16)   lgV=4,lglgV=2;
    for(int i=0;i<lgV;i++){
        vector<int> vec;
        for(int j=0;j<n;j++)if(j&(1<<i))vec.eb(j+1);
        ans.eb(vec);
    }
    for(int i=0;i<lglgV;i++){
        mems(c,0);
        vector<int> vec;
        for(int j=0;j<lgV;j++)if(j&(1<<i)){
            for(int k:ans[j])c[k]++;
        }
        for(int j=1;j<=n;j++)if(c[j]&1)vec.eb(j);
        ans.eb(vec);
    }
    mems(c,0);
    for(int i=0;i<lglgV;i++)for(int j:ans[lgV+i])c[j]++;
    ans.eb(vector<int>());
    for(int i=1;i<=n;i++)if(c[i]&1)ans.back().eb(i);
    int k=0;
    for(int i=0;i<ans.size();i++){
        if(ans[i].empty()){
            a[i]=1;
            continue;
        }
        printf("1 %d ",ans[i].size());
        for(int x:ans[i])printf("%d ",x);
        k++;
        puts("");
    }
    puts("2");fflush(stdout);
    for(int i=0,j=0;i<k;i++){
        while(ans[j].empty())j++;
        scanf("%d",&a[j]);j++;
    }
    // getdata();
    // printf("ans : ");for(int i=0;i<ans.size();i++)printf("%d ",a[i]);puts("");
    bool flag=a[14]!=(a[10]^a[11]^a[12]^a[13]);
    if(n<=16)   flag=a[6]!=(a[4]^a[5]);
    if(!flag){
        debug("ask [0,9] all true\n");
        int s=0;for(int i=0;i<lgV;i++)if(!a[i])s|=1<<i;
        s++;
        printf("%d\n",s);fflush(stdout);
        if(s==X)    debug("Accepted!\n");
        else    debug("Wrong Answer!\n");
        return 0;
    }
    int s=0;
    for(int i=0;i<lglgV;i++){
        bool flag=!a[i+lgV];
        for(int j=0;j<lgV;j++)if(j&(1<<i))flag^=!a[j];
        if(flag)    s|=1<<i;
    }
    s++;
    debug("%d is rat\n",s);
    a[s-1]^=1;
    s=0;for(int i=0;i<lgV;i++)if(!a[i])s|=1<<i;
    s++;
    printf("%d\n",s);fflush(stdout);
    if(s==X)    debug("Accepted!\n");
    else    debug("Wrong Answer!\n");
}