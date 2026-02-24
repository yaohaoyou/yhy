#include<bits/stdc++.h>
#define db double
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10;
int n,m,L,V;
int d[maxn],v[maxn],a[maxn],p[maxn];
inline bool check(int k,int i){
    if((p[k]-d[i]<0)||(a[i]<0&&((-1ll*v[i]*v[i])>2ll*(p[k]-d[i])*a[i])))   return false;
    return 1ll*v[i]*v[i]+2ll*a[i]*(p[k]-d[i])>1ll*V*V;
}
bool f[maxn];
pii vv[maxn],vec[maxn];int vvl,vecl;
priority_queue<pii,vector<pii>,greater<pii>> pq;
void init(){
    while(!pq.empty())pq.pop();
    vvl=vecl=0;
    mems(f,0);
}
void solve(){
    init();
    cin>>n>>m>>L>>V;
    for(int i=1;i<=n;i++)   cin>>d[i]>>v[i]>>a[i];
    for(int i=1;i<=m;i++)   cin>>p[i];
    int ans1=0;
    for(int i=1;i<=n;i++){
        if(a[i]<0){
            int k=lower_bound(p+1,p+m+1,d[i])-p;
            if(k>0&&k<=m&&p[k]>=d[i]){
                if(check(k,i)){
                    int l=k,r=m,res=k;
                    while(l<=r){
                        int mid=(l+r)>>1;
                        if(check(mid,i))  res=mid,l=mid+1;
                        else    r=mid-1;
                    }
                    vv[++vvl]=pii(k,res);
                    ans1++;
                }
            }
        }
        else{
            if(check(m,i)){
                int l=1,r=m,res=m;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(check(mid,i))    res=mid,r=mid-1;
                    else    l=mid+1;
                }
                vv[++vvl]=pii(res,m);
                ans1++;
            }
        }
    }
    sort(vv+1,vv+vvl+1,[&](pii x,pii y){return x.se>y.se;});
    for(int c=1;c<=vvl;c++){
        int l=vv[c].fi,r=vv[c].se;
        while(!pq.empty()&&pq.top().fi<=l){
            f[pq.top().se]=true;pq.pop();
        }
        pq.push(pii(l,c));
    }
    for(int c=1;c<=vvl;c++)
        if(!f[c])   vec[++vecl]=vv[c];
    sort(vec+1,vec+vecl+1);
    int ans2=0,r=0;
    for(int i=1;i<=vecl;i++){
        if(vec[i].fi>r){
            ans2++;
            r=vec[i].se;
        }
    }
    cout<<ans1<<' '<<m-ans2<<'\n';
}
int main(){
    // freopen("detect.in","r",stdin);freopen("detect.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--)  solve();
}