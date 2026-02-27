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
const int maxn=2e5+10;
int n;ll lim,ans=1e18;
int a[maxn],b[maxn];
vector<pii> v[2];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void matt(int _cases){
    ans=1e18;
    v[0].clear();v[1].clear();
    scanf("%d%lld",&n,&lim);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    ll s[2]={0,0};
    for(int i=1;i<=n;i++)   v[a[i]>0].eb(a[i],i),s[a[i]>0]+=a[i];
    sort(v[0].begin(),v[0].end(),greater<pii>());
    // if(_cases==365){
    //     printf("%lld:",lim);
    //     for(int i=1;i<=n;i++)printf("%d,",a[i]);
    //     for(int i=1;i<=n;i++)if(b[i])printf("%d\n",i);
    // }
    if(v[0].size()>=2){
        int x=v[0][0].se,y=v[0][1].se;
        if(abs(x-y)==1&&v[0].size()>2){
            y=v[0][2].se;
            if(abs(x-y)==1&&v[0].size()>3){
                x=v[0][1].se;y=v[0][2].se;
                if(abs(x-y)^1){
                    if(a[x]+a[y]>=lim)  ans=0;
                    else if(b[x]||b[y]) gmn(ans,lim-a[x]-a[y]);
                }
                x=v[0][0].se;y=v[0][3].se;
            }
        }
        if(abs(x-y)^1){
            if(a[x]+a[y]>=lim)  ans=0;
            else if(b[x]||b[y]) gmn(ans,lim-a[x]-a[y]);
        }
        int s=0;
        for(auto [x,i]:v[0]){
            if(!b[i])    continue;
            s++;
            for(int j=1;j<=i-2;j++)gmn(ans,lim-a[i]-a[j]);
            for(int j=i+2;j<=n;j++)gmn(ans,lim-a[i]-a[j]);
            if(s==10)    break;
        }
        ans=max(ans,0ll);
    }
    if(!v[1].empty()){
        if(v[1].back().se-v[1].front().se+1!=v[1].size()){
            if(s[1]>=lim)   return puts("0"),void();
            else if(count_if(v[1].begin(),v[1].end(),[&](pii x){return b[x.se];}))   gmn(ans,lim-s[1]);
            else{
                int l=v[1].front().se,r=v[1].back().se;
                for(int i=1;i<=n;i++){
                    if(!b[i])   continue;
                    if(v[1].size()+(i>=l&&i<=r)==r-l+1){
                        for(int j=l+1;j<r;j++)if(!b[j])gmn(ans,lim-(s[1]+a[i]-a[j]));
                        for(int j=1;j<l-1;j++)  gmn(ans,lim-(s[1]+a[i]+a[j]));
                        for(int j=r+2;j<=n;j++)gmn(ans,lim-(s[1]+a[i]+a[j]));
                        if(l>1) gmn(ans,lim-(s[1]+a[i]-a[l]+a[l-1]));
                        if(r<n) gmn(ans,lim-(s[1]+a[i]-a[r]+a[r+1]));
                    }
                    else    gmn(ans,lim-(s[1]+a[i]));
                }
            }
        }
        else{
            int l=v[1].front().se,r=v[1].back().se,cnt=count(b+l,b+r+1,1);
            for(int i=l+1;i<r;i++)if(s[1]-a[i]>=lim)ans=0;
            for(pii i:v[0])if(i.se!=l-1&&i.se!=r+1&&s[1]+i.fi>=lim)ans=0;
            if(v[1].size()>=2){
                int x=v[1].front().se;
                if(x>1&&s[1]-a[x]+a[x-1]>=lim)  ans=0;
                x=v[1].back().se;
                if(x<n&&s[1]-a[x]+a[x+1]>=lim)  ans=0;
            }
            if(!ans)    return puts("0"),void();
            for(int i=l+1;i<r;i++){
                if(cnt-b[i])    gmn(ans,lim-(s[1]-a[i]));
            }
            for(int i=1;i<l-1;i++){
                if(cnt+b[i])    gmn(ans,lim-(s[1]+a[i]));
            }
            for(int i=r+2;i<=n;i++){
                if(cnt+b[i])    gmn(ans,lim-(s[1]+a[i]));
            }
            if(v[1].size()>1){
                if(l>1&&(cnt-b[l]+b[l-1]))  gmn(ans,lim-(s[1]-a[l]+a[l-1]));
                if(r<n&&(cnt-b[r]+b[r+1]))  gmn(ans,lim-(s[1]-a[r]+a[r+1]));
            }
            int c=0;
            for(auto [x,i]:v[0]){
                if(!b[i])    continue;
                c++;
                if(i<l-1||i>r+1)    gmn(ans,lim-(s[1]+a[i]));
                else{
                    for(int j=1;j<=min(l,i)-2;j++)gmn(ans,lim-(s[1]+a[i]+a[j]));
                    int L=min(l,i),R=max(r,i);
                    for(int j=L+1;j<R;j++)if(cnt+1-b[j])gmn(ans,lim-(s[1]+a[i]-a[j]));
                    for(int j=max(r,i)+2;j<=n;j++)gmn(ans,lim-(s[1]+a[i]+a[j]));
                    if(L>1&&(i^L)) gmn(ans,lim-(s[1]+a[i]-a[L]+a[L-1]));
                    if(R<n&&(i^R)) gmn(ans,lim-(s[1]+a[i]-a[R]+a[R+1]));
                }
                if(c==10)    break;
            }
        }
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}