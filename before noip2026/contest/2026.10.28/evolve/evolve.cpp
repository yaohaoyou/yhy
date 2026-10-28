#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define psi pair<string,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=5010;
int n;
psi a[maxn];
vector<string> ans[3];
bool chk(string x,string y){
    if(x.empty())return true;
    int p=0;
    for(int i=0;i<y.length();i++)if(y[i]==x[p]){p++;if(p==x.length())return true;}
    return false;
}
bool mem2;
int main(){
    freopen("evolve.in","r",stdin);freopen("evolve.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    cin>>n;
    for(int i=0;i<=n;i++)   cin>>a[i].fi,a[i].se=i;
    sort(a,a+n+1,[&](psi x,psi y){return x.fi.length()==y.fi.length()?x.se>y.se:x.fi.length()<y.fi.length();});
    if(a[n].se) return puts("impossible"),0;
    for(int i=0;i<n;i++)if(!chk(a[i].fi,a[n].fi))return puts("impossible"),0;
    ans[0].eb(a[0].fi);
    for(int i=1;i<n;i++){
        bool x=chk(ans[0].back(),a[i].fi),y=ans[1].empty()||chk(ans[1].back(),a[i].fi);
        if(!x&&!y)  return puts("impossible"),0;
        if(x&&y){
            if(ans[2].empty()||chk(ans[2].back(),a[i].fi))  ans[2].eb(a[i].fi);
            else{
                for(string j:ans[2])ans[0].eb(j);ans[2].clear();
                ans[1].eb(a[i].fi);
            }
        }
        else if(x){
            ans[0].eb(a[i].fi);
            for(string j:ans[2])ans[1].eb(j);ans[2].clear();
        }
        else{
            ans[1].eb(a[i].fi);
            for(string j:ans[2])ans[0].eb(j);ans[2].clear();
        }
        // if(chk(a[j].fi,a[i].fi)){
        //     ans[0].eb(a[i].fi);
        //     j=i;
        // }
        // else    ans[1].eb(a[i].fi);
    }
    for(string j:ans[2])ans[0].eb(j);
    // reverse(ans[0].begin(),ans[0].end());reverse(ans[1].begin(),ans[1].end());
    // string lst=a[n].fi;
    // for(string i:ans[0])if(!chk(i,lst))return puts("impossible"),0;else lst=i;
    // lst=a[n].fi;
    // for(string i:ans[1])if(!chk(i,lst))return puts("impossible"),0;else lst=i;
    // reverse(ans[0].begin(),ans[0].end());reverse(ans[1].begin(),ans[1].end());
    cout<<ans[0].size()<<' '<<ans[1].size()<<'\n';
    for(string i:ans[0])    cout<<i<<'\n';
    for(string i:ans[1])    cout<<i<<'\n';
}